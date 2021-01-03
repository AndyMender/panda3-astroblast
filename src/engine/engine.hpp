
#pragma once


namespace ab_engine
{
    /// Main game engine
    class Engine 
    {
        public:
            Engine();
            ~Engine();

            // TODO: add support for reading configuration file and default config?

            // engine is unique - cannot copy/move!
            Engine(const Engine&) = delete;
            Engine(const Engine&&) = delete;	// move constructor
            Engine& operator=(const Engine&) = delete;
            Engine& operator=(Engine&&) = delete; // move + assignment

            // show state
            constexpr bool is_initialized() const { return this->initialized; };
            void print_version() const;

            void run_main_loop();

        private:
            // engine state
            bool initialized = false;

            // init player state
            // TODO: move init to level code?
            // TODO: init requires a blueprint now!

            // entity collections

            // initial setup
            void init();
	
            // updating
            void update();

            // collisions

            // drawing
            void draw() const;

            // cleanup
	        void tear_down();
    };
} // namespace ab_engine
