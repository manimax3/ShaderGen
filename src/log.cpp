#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

spdlog::logger &sg::CreateLogger()
{
    static auto logger = spdlog::stdout_color_mt("console");
    logger->set_level(spdlog::level::trace);
    return *logger;
}
