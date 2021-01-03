

#include "common.hpp"

namespace ab_common
{
    void log_message(const std::string_view message, const AppLogLevel level)
    {
        if (level > Verbosity) return;

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
                const uint8_t verbosity = static_cast<uint8_t>(level);
                BOOST_LOG_TRIVIAL(fatal) << "Unsupported log level found: " << std::to_string(verbosity);
        }
    }

} // namespace ab_common