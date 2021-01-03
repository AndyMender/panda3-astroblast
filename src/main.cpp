
#include <cstdlib>

#include <panda3d/pandaFramework.h>
#include <panda3d/pandaSystem.h>

#include "main.hpp"

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
    WindowFramework* window = framework.open_window();

    // Here is room for your own code

    // Do the main loop, equal to run() in python
    framework.main_loop();
    framework.close_framework();

    ab_common::log_message("All tasks finished. Exiting!", ab_common::AppLogLevel::Info);

    return EXIT_SUCCESS;
}
