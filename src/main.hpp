
#pragma once

#include <cstdint>
#include <iostream>

#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/errors.hpp>

#include "common/common.hpp"

namespace ab_main
{
    /// Allowed command-line exit codes
    enum class CmdlineCode: uint8_t
    {
        Success,
        Help,
        Error
    };

    /// Parse command-line arguments using 'boost::program_options'
    CmdlineCode process_cmdline_args(int argc, char* argv[]) 
    {
        namespace po = boost::program_options;

        uint8_t verbosity;

        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
        ("help,h", "Print this help message")
        ("verbosity,v", po::value<uint8_t>(), "Set verbosity level")
        ;

        // Parse command-line arguments
        // NOTE: catch exception on failed parsing
        po::variables_map argumentMap;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), argumentMap);
            po::notify(argumentMap);
        }
        catch (po::invalid_command_line_syntax e)
        {
            ab_common::log_message("Failed to process command-line arguments. Use --help for possible options.", ab_common::AppLogLevel::Error);
            return CmdlineCode::Error;
        }

        // Handle argument values
        if (argumentMap.count("help"))
        {
            std::cout << desc << std::endl;
            return CmdlineCode::Help;
        }

        if (argumentMap.count("verbosity"))
        {
            verbosity = argumentMap["verbosity"].as<uint8_t>();
            ab_common::Verbosity = static_cast<ab_common::AppLogLevel>(verbosity);

            ab_common::log_message("Setting verbosity to: " + std::to_string(verbosity), ab_common::AppLogLevel::Info);
        }
        else
        {
            ab_common::log_message("Using default verbosity value of: " + std::to_string(verbosity), ab_common::AppLogLevel::Info);
        }

        return CmdlineCode::Success;
    }

} // namespace ab_main
