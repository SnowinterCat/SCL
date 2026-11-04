#pragma once
#include <scl/config.hpp>

// define SCL_FORCE_EXPORT_API
#if defined(_WIN32)
    #define SCL_FORCE_EXPORT_API __declspec(dllexport)
#endif
#if !defined(SCL_FORCE_EXPORT_API)
    #if defined(__GNUC__) && (__GNUC__ >= 4)
        #define SCL_FORCE_EXPORT_API __attribute__((visibility("default")))
    #else
        #define SCL_FORCE_EXPORT_API
    #endif
#endif
