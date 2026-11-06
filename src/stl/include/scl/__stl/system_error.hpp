#pragma once
#include <scl/__stl/configuration.hpp>
// Standard Library
#include <system_error>
// System Library
// Third-Party Library
// Local Library

namespace mylib_detail
{
    void make_error_code() = delete;
}

class ErrorCode {
public:
    using Category = std::error_category;

    ErrorCode() noexcept : _code(0), _para(0), _cat(&std::system_category()) {}
    ErrorCode(int32_t code, int32_t para, const Category &cat) noexcept
        : _code(code), _para(para), _cat(&cat)
    {
    }
    ErrorCode(int32_t code, int16_t para1, int16_t para2, const Category &cat) noexcept
        : _code(code),
          // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
          _para(static_cast<int32_t>((static_cast<uint32_t>(static_cast<uint16_t>(para2)) << 16) |
                                     static_cast<uint32_t>(static_cast<uint16_t>(para1)))),
          _cat(&cat)
    {
    }

    ErrorCode(std::error_code ec) noexcept : _code(ec.value()), _para(), _cat(&ec.category()) {}
    explicit operator std::error_code() const noexcept { return {_code, *_cat}; }

    template <class Ep>
    ErrorCode(Ep errc) noexcept // NOLINT(cppcoreguidelines-pro-type-member-init): all members
                                // are overwritten by the assignment below before any use.
        requires std::is_error_code_enum_v<Ep>
    {
        using mylib_detail::make_error_code;
        *this = make_error_code(errc);
    }
    template <class Ep>
    auto operator=(Ep errc) noexcept -> ErrorCode &
        requires std::is_error_code_enum_v<Ep>
    {
        using mylib_detail::make_error_code;
        *this = make_error_code(errc);
        return *this;
    }

    void assign(int32_t code, int32_t para, const Category &cat) noexcept
    {
        _code = code;
        _para = para;
        _cat  = &cat;
    }
    void clear() noexcept
    {
        _code = 0;
        _para = 0;
        _cat  = &std::system_category();
    }

    [[nodiscard]] auto value() const noexcept -> int32_t { return _code; }
    [[nodiscard]] auto category() const noexcept -> const Category & { return *_cat; }
    [[nodiscard]] auto para() const noexcept -> int32_t { return _para; }
    [[nodiscard]] auto para1() const noexcept -> int16_t
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
        return static_cast<int16_t>(static_cast<uint32_t>(_para) & 0xFFFFU);
    }
    [[nodiscard]] auto para2() const noexcept -> int16_t
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
        return static_cast<int16_t>((static_cast<uint32_t>(_para) >> 16) & 0xFFFFU);
    }

    [[nodiscard]] explicit operator bool() const noexcept { return _code != 0; }
    [[nodiscard]] auto     message() const -> std::string { return _cat->message(_code); }
    [[nodiscard]] auto     default_error_condition() const noexcept -> std::error_condition
    {
        return _cat->default_error_condition(_code);
    }

protected:
    int32_t         _code;
    int32_t         _para; // Or [31:16]=para2, [15:0]=para1
    const Category *_cat;
};

// compare operator
inline auto operator==(const ErrorCode &err1, const ErrorCode &err2) noexcept -> bool
{
    return err1.value() == err2.value() && err1.category() == err2.category();
}
inline auto operator!=(const ErrorCode &err1, const ErrorCode &err2) noexcept -> bool
{
    return !(err1 == err2);
}

// ErrorCode with error_condition
inline auto operator==(const ErrorCode &err1, const std::error_condition &err2) noexcept -> bool
{
    return err1.default_error_condition() == err2;
}
inline auto operator==(const std::error_condition &err1, const ErrorCode &err2) noexcept -> bool
{
    return err2 == err1;
}
inline auto operator!=(const ErrorCode &err1, const std::error_condition &err2) noexcept -> bool
{
    return !(err1 == err2);
}
inline auto operator!=(const std::error_condition &err1, const ErrorCode &err2) noexcept -> bool
{
    return !(err2 == err1);
}

// ErrorCode with std::error_code
inline auto operator==(const ErrorCode &err1, const std::error_code &err2) noexcept -> bool
{
    return err1.value() == err2.value() && err1.category() == err2.category();
}
inline auto operator!=(const ErrorCode &err1, const std::error_code &err2) noexcept -> bool
{
    return !(err1 == err2);
}
inline auto operator==(const std::error_code &err1, const ErrorCode &err2) noexcept -> bool
{
    return err2 == err1;
}
inline auto operator!=(const std::error_code &err1, const ErrorCode &err2) noexcept -> bool
{
    return !(err2 == err1);
}