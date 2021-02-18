#pragma once
#include <PCH/sfmxpch.hpp>

namespace masterX
{
    class Log
    {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
        static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };
}

#ifdef MASTER_DEBUG

// Core log macros
#define MASTER_CORE_TRACE(...)      ::masterX::Log::getCoreLogger()->trace(__VA_ARGS__)
#define MASTER_CORE_INFO(...)       ::masterX::Log::getCoreLogger()->info(__VA_ARGS__)
#define MASTER_CORE_WARN(...)       ::masterX::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MASTER_CORE_ERROR(...)      ::masterX::Log::getCoreLogger()->error(__VA_ARGS__)
#define MASTER_CORE_CRITICAL(...)   ::masterX::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define MASTER_TRACE(...)      ::masterX::Log::getClientLogger()->trace(__VA_ARGS__)
#define MASTER_INFO(...)       ::masterX::Log::getClientLogger()->info(__VA_ARGS__)
#define MASTER_WARN(...)       ::masterX::Log::getClientLogger()->warn(__VA_ARGS__)
#define MASTER_ERROR(...)      ::masterX::Log::getClientLogger()->error(__VA_ARGS__)
#define MASTER_CRITICAL(...)   ::masterX::Log::getClientLogger()->critical(__VA_ARGS__)

#else

#define MASTER_CORE_TRACE(...)
#define MASTER_CORE_INFO(...)    
#define MASTER_CORE_WARN(...)
#define MASTER_CORE_ERROR(...)
#define MASTER_CORE_CRITICAL(...)

// Client log macros
#define MASTER_TRACE(...)
#define MASTER_INFO(...)
#define MASTER_WARN(...)
#define MASTER_ERROR(...)
#define MASTER_CRITICAL(...)

#endif