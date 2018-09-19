#pragma once
#include "spdlog/spdlog.h"

namespace sg {

spdlog::logger &CreateLogger();

inline auto &Log()
{
    static auto &_logger = CreateLogger();
    return _logger;
}
}
