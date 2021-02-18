#ifdef MASTER_VS_COMPILER
    #include <sfmxpch.hpp>
#endif

#include "Log.hpp"

namespace masterX
{
    std::shared_ptr<spdlog::logger> Log::s_coreLogger;
    std::shared_ptr<spdlog::logger> Log::s_clientLogger;

    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n : %v%$");

        s_coreLogger = spdlog::stdout_color_mt("CORE");
        s_clientLogger = spdlog::stdout_color_mt("CLIENT");
    }
}