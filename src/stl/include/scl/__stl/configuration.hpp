#pragma once
#include <scl/config.hpp>
// Standard Library
#include <version>

// SCL_STL_API
#if defined(_WIN32) && defined(SCL_SHARED_BUILD)
    #if defined(SCL_STL_COMPILING)
        #define SCL_STL_API __declspec(dllexport)
    #else
        #define SCL_STL_API __declspec(dllimport)
    #endif
#endif
#if !defined(SCL_STL_API)
    #if !defined(SCL_NO_GCC_API_ATTRIBUTE) && defined(__GNUC__) && (__GNUC__ >= 4)
        #define SCL_STL_API __attribute__((visibility("default")))
    #else
        #define SCL_STL_API
    #endif
#endif
#if !defined(SCL_STL_HIDDEN_API)
    #if !defined(SCL_NO_GCC_API_ATTRIBUTE) && defined(__GNUC__) && (__GNUC__ >= 4)
        #define SCL_STL_HIDDEN_API __attribute__((visibility("hidden")))
    #else
        #define SCL_STL_HIDDEN_API
    #endif
#endif

#define SCL_STL_BEGIN                                                                              \
    namespace stl                                                                                  \
    {
#define SCL_STL_END }

// clang-format off
#define SCL_STL_LOG_TRACE(...)    SPDLOG_TRACE(__VA_ARGS__)
#define SCL_STL_LOG_DEBUG(...)    SPDLOG_DEBUG(__VA_ARGS__)
#define SCL_STL_LOG_INFO(...)     SPDLOG_INFO(__VA_ARGS__)
#define SCL_STL_LOG_WARN(...)     SPDLOG_WARN(__VA_ARGS__)
#define SCL_STL_LOG_ERROR(...)    SPDLOG_ERROR(__VA_ARGS__)
#define SCL_STL_LOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)
// clang-format on
