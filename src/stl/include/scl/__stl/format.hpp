#pragma once
#include <scl/__stl/configuration.hpp>
// Standard Library
#include <version>
// fmtlib
#if __cpp_lib_format >= 202311L
    #include <format>
#else
    #include <fmt/xchar.h>
#endif

SCL_BEGIN
SCL_STL_BEGIN

#if __cpp_lib_format >= 202311L
// 核心格式化函数
using std::format;
using std::format_to;
using std::format_to_n;
using std::formatted_size;
using std::vformat;
using std::vformat_to;
// 格式化器
using std::formatter;
// 参数相关
using std::basic_format_arg;
using std::basic_format_context;
using std::basic_format_parse_context;
using std::format_args;
// 字符串类型
using std::basic_format_string;
using std::format_string;
using std::wformat_string;
// 结果类型
using std::format_to_n_result;
// 异常类型
using std::format_error;
// 类型特征
// using std::format_kind;
#else
// 核心格式化函数
using fmt::format;
using fmt::format_to;
using fmt::format_to_n;
using fmt::formatted_size;
using fmt::vformat;
using fmt::vformat_to;
// 格式化器
using fmt::formatter;
// 参数相关
using fmt::basic_format_arg;
using fmt::basic_format_context;
using fmt::basic_format_parse_context;
using fmt::format_args;
// 字符串类型
using fmt::basic_format_string;
using fmt::format_string;
using fmt::wformat_string;
// 结果类型
using fmt::format_to_n_result;
// 异常类型
using fmt::format_error;
// 类型特征
// using fmt::format_kind;
#endif

SCL_STL_END
SCL_END