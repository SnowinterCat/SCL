#include <scl/config.hpp>
// Standard Library
#include <iostream>
// System Library
// Third-Party Library
// Local Library
#include "scl/stl.hpp"

auto aaa() -> scl::stl::expected<int, std::error_code>
{
    return 0;
    // return scl::stl::unexpected(std::make_error_code(std::errc::io_error));
}

class ErrorCode {
    using Category = std::error_category;

    ErrorCode(std::error_code ec) noexcept : _code(ec.value()), para(0), _cat(&ec.category()) {}

    explicit operator std::error_code() const noexcept { return {_code, *_cat}; }

protected:
    int32_t _code;
    union {
        int32_t para;
        struct {
            int16_t para1{};
            int16_t para2{};
        };
    };
    const Category *_cat;
};

auto main() -> int
{
    auto aaaa = ({
        auto res = aaa();
        if (!res) {
            return 0;
        }
        *res;
    });
    std::cout << "hello world\n" << aaaa;
    return 0;
}