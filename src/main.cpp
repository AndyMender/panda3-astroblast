
#include <cstdlib>

#include "main.hpp"

int main(int argc, char* argv[])
{
    /* Process command-line args */
    ab_main::CmdlineCode exit_code = ab_main::process_cmdline_args(argc, argv);

    ab_common::log_message("Command-line parameters processed.", ab_common::AppLogLevel::Info);

    /* Triggered 'help' message */
    if (exit_code == ab_main::CmdlineCode::Help)
    {
        return EXIT_SUCCESS;
    } 
    else if (exit_code == ab_main::CmdlineCode::Error)
    {
        ab_common::log_message("Processing command-line arguments failed. Exiting!", ab_common::AppLogLevel::Fatal);
        return EXIT_FAILURE;
    }

    ab_common::log_message("All tasks finished. Exiting!", ab_common::AppLogLevel::Info);

    return EXIT_SUCCESS;
}
