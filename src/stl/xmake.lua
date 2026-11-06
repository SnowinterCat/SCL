target("stl")
    set_kind("headeronly")

    add_deps("config")
    add_packages(
        has_config("has_std_out_ptr")        and nil or "out_ptr",
        has_config("has_std_expected")       and nil or "zeus_expected",
        has_config("has_std_runtime_format") and nil or "fmt",
        {public = true}
    )

    add_includedirs("include", {public = true})
    add_headerfiles("include/(**)")
target_end()