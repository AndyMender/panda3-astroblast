
#pragma once

#include <cstdint>
#include <iostream>

#include <boost/log/trivial.hpp>


namespace ab_common
{
    /// Allowed verbosity levels
    enum class AppLogLevel: std::uint16_t
    { 
        Fatal,
        Warning, 
        Error, 
        Info, 
        Debug
    };

    /// Default verbosity level
    AppLogLevel Verbosity = AppLogLevel::Error;

    /// Print a logging message
    void log_message(const std::string_view message, const AppLogLevel level);

} // namespace ab_common
