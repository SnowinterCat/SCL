#pragma once
#include <scl/__stl/configuration.hpp>
// Standard Library
#include <version>
// outptrlib
#if defined(__cpp_lib_out_ptr)
    #include <memory>
#else
    #include <memory>
    #include <ztd/out_ptr.hpp>
#endif

SCL_BEGIN
SCL_STL_BEGIN

#if defined(__cpp_lib_out_ptr)
using std::out_ptr;
#else
using ztd::out_ptr::out_ptr;
#endif

SCL_STL_END
SCL_END