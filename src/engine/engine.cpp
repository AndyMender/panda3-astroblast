
#include <cstdlib>
#include <ctime>

#include <panda3d/pandaVersion.h>

#include "engine.hpp"
#include "../common/common.hpp"


namespace ab_engine {
    /// Default constructor
    Engine::Engine()
    {
        this->init();

        if (this->is_initialized())
        {
            ab_common::log_message("Engine initialized successfully.", ab_common::AppLogLevel::Info);
        }
        else
        {
            ab_common::log_message("Engine initialized successfully.", ab_common::AppLogLevel::Error);
        }
    }

    //// Default destructor
    Engine::~Engine()
    {
        if (this->is_initialized())
        {
            this->tear_down();          
        }

        if (!this->is_initialized())
        {
            ab_common::log_message("Engine terminated successfully.", ab_common::AppLogLevel::Info);
        }
        else
        {
            ab_common::log_message("Engine termination failed!", ab_common::AppLogLevel::Error);
        }
    }

    void Engine::print_version() const
    {
        const std::string error_str = "Running panda3d version " + std::string(PANDA_VERSION_STR);
        ab_common::log_message(error_str, ab_common::AppLogLevel::Info);
    }

    /// Engine initialization and resource allocation 
    void Engine::init()
    {
        // seed the RNG
        std::srand(std::time(nullptr));

        this->initialized = true;
    }

    /// Engine clean-up and deallocation
    void Engine::tear_down() {

        this->initialized = false;
    }

    /// Run main engine loop
    void Engine::run_main_loop() {

    }

    /// Update all states
    void Engine::update() {
        // update engine

        // update player (event-less behavior)

        // update enemies

        // update bullets
    }

    /// Draw background and all objects
    void Engine::draw() const {
        // draw background

        // draw player

        // draw enemies

        // draw bullets

        // draw HUD

        // draw stencils for debugging
    }

} // namespace ab_engine
