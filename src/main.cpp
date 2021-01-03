
#include <cstdlib>

#include "main.hpp"

int main(int argc, char* argv[])
{
    /* Process command-line args */
    ab_main::CmdlineCode exitCode = ab_main::process_cmdline_args(argc, argv);

    /* Triggered 'help' message */
    if (exitCode == ab_main::CmdlineCode::Help)
    {
        return EXIT_SUCCESS;
    } 
    else if (exitCode == ab_main::CmdlineCode::Error)
    {
        ab_common::log_message("Processing command-line arguments failed. Exiting!", ab_common::AppLogLevel::Fatal);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
