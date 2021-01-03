

#include "common.hpp"

namespace ab_common
{
    void log_message(const std::string_view message, const AppLogLevel level)
    {
        const uint16_t level_int = static_cast<std::uint16_t>(level);
        const uint16_t verbosity = static_cast<std::uint16_t>(Verbosity);

        if (level_int > verbosity) return;

        // TODO: Make selector less repetitive?
        switch(level) {
            case AppLogLevel::Fatal:
                BOOST_LOG_TRIVIAL(fatal) << message;
                break;
            case AppLogLevel::Error:
                BOOST_LOG_TRIVIAL(error) << message;
                break;
            case AppLogLevel::Warning:
                BOOST_LOG_TRIVIAL(warning) << message;
                break;
            case AppLogLevel::Info:
                BOOST_LOG_TRIVIAL(info) << message;
                break;
            case AppLogLevel::Debug:
                BOOST_LOG_TRIVIAL(debug) << message;
                break;
            default:
                BOOST_LOG_TRIVIAL(fatal) << "Unsupported log level found: " << std::to_string(level_int);
        }
    }

} // namespace ab_common