
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <cmath>

#include <panda3d/pandaFramework.h>
#include <panda3d/pandaSystem.h>

#include <panda3d/genericAsyncTask.h>
#include <panda3d/asyncTaskManager.h>

#include <panda3d/cIntervalManager.h>
#include <panda3d/cLerpNodePathInterval.h>
#include <panda3d/cMetaInterval.h>

#include "main.hpp"

// TODO: attach task manager, clock and camera to engine
// The global task manager
PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
// The global clock
PT(ClockObject) globalClock = ClockObject::get_global_clock();
// Here's what we'll store the camera in.
NodePath camera;

// This is our task - a global or static function that has to return DoneStatus.
// The task object is passed as argument, plus a void* pointer, containing custom data.
// For more advanced usage, we can subclass AsyncTask and override the do_task method.
AsyncTask::DoneStatus spinCameraTask(GenericAsyncTask *task, void *data)
{
  // Calculate the new position and orientation (inefficient - change me!)
  double elapsed_time = globalClock->get_real_time();
  // Rotation speed at N degrees/s (capped to prevent overflows)
  double angledegrees = std::fmod(elapsed_time * 8.0, 360.0);
  double angleradians = angledegrees * (M_PI / 180.0);
  // NOTE: changing camera position is not mandatory when doing a centered rotation
  camera.set_pos(20 * sin(angleradians), -20.0 * cos(angleradians), 3);
  camera.set_hpr(angledegrees, 0, 0);

  // Tell the task manager to continue this task the next frame.
  // Pass AsyncTask::DS_done if it's a oneshot task
  return AsyncTask::DS_cont;
}

// Make the panda walk
AsyncTask::DoneStatus pandaWalk(GenericAsyncTask *task, void *data)
{
    // Step the interval manager
    CIntervalManager::get_global_ptr()->step();

    return AsyncTask::DS_cont;
}


int main(int argc, char* argv[])
{
    // Process command-line args
    ab_main::CmdlineCode exit_code = ab_main::process_cmdline_args(argc, argv);
    ab_common::log_message("Command-line parameters processed.", ab_common::AppLogLevel::Info);

    // Triggered 'help' message
    if (exit_code == ab_main::CmdlineCode::Help)
    {
        return EXIT_SUCCESS;
    } 
    // Failed to process command-line arguments
    else if (exit_code == ab_main::CmdlineCode::Error)
    {
        ab_common::log_message("Processing command-line arguments failed. Exiting!", ab_common::AppLogLevel::Fatal);
        return EXIT_FAILURE;
    }

    // Open a new window framework
    PandaFramework framework;
    framework.open_framework(argc, argv);

    // Set the window title and open the window
    framework.set_window_title("Astroblast");
    PT(WindowFramework) window = framework.open_window();

    if (window != nullptr)
    {
        ab_common::log_message("Window created successfully!", ab_common::AppLogLevel::Info);
    }

    // Set extra window params
    window->set_lighting(true);
    window->set_wireframe(false);

    // Get the camera NODE and store it in a variable.
    camera = window->get_camera_group();

    // Load environment model as main scene and attach to graph's root ("render")
    NodePath scene = window->load_model(framework.get_models(), "models/environment");
    scene.reparent_to(window->get_render());

    // Apply scale and position transforms to scene in  x,y,z
    scene.set_scale(0.25, 0.25, 0.25);
    // NOTE: The position of the main model
    scene.set_pos(-8, 42, 0);

    // Load a panda model, set scale and attach to graph's root
    NodePath pandaActor = window->load_model(framework.get_models(), "models/panda-model");
    pandaActor.set_scale(0.005);    // scale only in x
    pandaActor.reparent_to(window->get_render());

    // Load walk anim from the panda model
    window->load_model(pandaActor, "models/panda-walk4");
    // Bind models and anims
    window->loop_animations(0);

    // Create the lerp intervals needed to walk back and forth
    PT(CLerpNodePathInterval) pandaPosInterval1, pandaPosInterval2, pandaHprInterval1, pandaHprInterval2;

    // Walk from (0, 10, 0) to (0, -10, 0)
    pandaPosInterval1 = new CLerpNodePathInterval("pandaPosInterval1", 16.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
    pandaPosInterval1->set_start_pos(LPoint3(0, 10, 0));
    pandaPosInterval1->set_end_pos(LPoint3(0, -10, 0));

    // Turn around (180 degrees)
    pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 1.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
    pandaHprInterval1->set_start_hpr(LPoint3(0, 0, 0));
    pandaHprInterval1->set_end_hpr(LPoint3(180, 0, 0));

    // Walk from (0, -10, 0) to (0, 10, 0)
    pandaPosInterval2 = new CLerpNodePathInterval("pandaPosInterval2", 16.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
    pandaPosInterval2->set_start_pos(LPoint3(0, -10, 0));
    pandaPosInterval2->set_end_pos(LPoint3(0, 10, 0));

    // Turn around (180 degrees)
    pandaHprInterval2 = new CLerpNodePathInterval("pandaHprInterval2", 1.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
    pandaHprInterval2->set_start_hpr(LPoint3(180, 0, 0));
    pandaHprInterval2->set_end_hpr(LPoint3(0, 0, 0));

    // Create and play the sequence that coordinates the intervals
    PT(CMetaInterval) pandaPace;
    pandaPace = new CMetaInterval("pandaPace");
    pandaPace->add_c_interval(pandaPosInterval1, 0, CMetaInterval::RS_previous_end);
    pandaPace->add_c_interval(pandaHprInterval1, 0, CMetaInterval::RS_previous_end);
    pandaPace->add_c_interval(pandaPosInterval2, 0, CMetaInterval::RS_previous_end);
    pandaPace->add_c_interval(pandaHprInterval2, 0, CMetaInterval::RS_previous_end);
    pandaPace->loop();

    // Enable controls
    // window->enable_keyboard();
    // window->setup_trackball(); // for camera control

    // Add tasks
    // If we specify custom data instead of NULL, it will be passed as the second argument
    // to the task function.
    taskMgr->add(new GenericAsyncTask("Spin the camera", &spinCameraTask, nullptr));
    taskMgr->add(new GenericAsyncTask("Walk the panda in a line", &pandaWalk, nullptr));

    // Start the main loop (frame rendering, background tasks/updates, etc.)
    framework.main_loop();

    // Destroy window framework
    framework.close_framework();

    ab_common::log_message("All tasks finished. Exiting!", ab_common::AppLogLevel::Info);

    return EXIT_SUCCESS;
}
