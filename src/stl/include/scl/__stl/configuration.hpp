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
