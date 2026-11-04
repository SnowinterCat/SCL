#pragma once
#include <scl/__stl/configuration.hpp>
// Standard Library
#include <version>
// expectedlib
#if defined(__cpp_lib_expected)
    #include <expected>
#else
    #include <zeus/expected.hpp>
#endif

SCL_BEGIN
SCL_STL_BEGIN

#if defined(__cpp_lib_expected)
using std::bad_expected_access;
using std::expected;
using std::unexpect;
using std::unexpect_t;
using std::unexpected;
#else
using zeus::bad_expected_access;
using zeus::expected;
using zeus::unexpect;
using zeus::unexpect_t;
using zeus::unexpected;
#endif

SCL_STL_END
SCL_END