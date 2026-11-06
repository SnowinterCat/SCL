-- 工程设置
set_project("SimpleCompatibilityLayer")
set_version("0.0.1", {build = tostring(get_config("buildversion")), soname = true})
-- set_xmakever("3.0.0")
option("alias", {showmenu = false, default = "scl"}) -- 工程名缩写

set_configvar("LEGAL_COPYRIGHT", "Copyright (C) 2026 SnowinterCat")
set_configvar("PROJECT_NAME", "SimpleCompatibilityLayer")

-- 全局设置
option("stdc",   {showmenu = true, default = 23, values = {23, 17}})
option("stdcxx", {showmenu = true, default = 23, values = {26, 23, 20, 17}})
function stdc()   return "c"   .. tostring(get_config("stdc"))   end
function stdcxx() return "c++" .. tostring(get_config("stdcxx")) end

set_languages(stdc(), stdcxx())
set_warnings("allextra")
set_encodings("utf-8")
set_exceptions("no-cxx")

-- 添加编译选项
add_rules("mode.release", "mode.debug", "mode.releasedbg", "mode.minsizerel")
add_rules("plugin.compile_commands.autoupdate", {lsp = "clangd", outputdir = ".vscode"})

-- 编译设置
option("3rd_custom",   {showmenu = true, type = "boolean", default = false})
option("3rd_kind",     {showmenu = true, type = "string",  default = get_config("kind"), values = {"static", "shared"}})
option("3rd_mode",     {showmenu = true, type = "string",  default = "release",          values = {"release", "debug"}})
option("outputdir",    {showmenu = true, type = "string",  default = path.join(os.projectdir(), "bin")})
option("buildversion", {showmenu = true, type = "number",  default = 0})
option("system",       {showmenu = true, type = "boolean", default = nil})

includes("lua/check")
check_macros("has_std_out_ptr",         "__cpp_lib_out_ptr",            {languages = stdcxx(), includes = "version"})
check_macros("has_std_expected",        "__cpp_lib_expected",           {languages = stdcxx(), includes = "version"})
check_macros("has_std_runtime_format",  "__cpp_lib_format >= 202311L",  {languages = stdcxx(), includes = "version"})

-- 隐藏设置、隐藏目标、打包命令
includes("lua/hideoptions.lua")
includes("lua/hidetargets.lua")
includes("lua/pack.lua")

-- some of the required libraries use our own repository
add_repositories("myrepo 3rd", {rootdir = os.scriptdir()})
-- detected libraries
-- if not is_plat("android") then add_requires("vulkansdk") end
-- header-only libraries
if not has_config("has_std_out_ptr")  then add_requires("out_ptr") end
if not has_config("has_std_expected") then add_requires("zeus_expected") end
-- normal libraries
if not has_config("has_std_runtime_format") then add_requires("fmt") end


if not has_config("3rd_custom") then
-- configurations of required libraries
add_requireconfs("**out_ptr",       {override = true, version = "x.x.x", system = get_config("system")})
add_requireconfs("**zeus_expected", {override = true, version = "x.x.x", system = get_config("system")})
add_requireconfs("**fmt",           {override = true, version = "x.x.x", system = get_config("system"), configs = {shared = is_config("3rd_kind", "shared"), debug = is_config("3rd_mode", "debug"), header_only = false}})
-- configurations of dependency libraries
end

-- subdirectories
includes("src/*/xmake.lua")
includes("test/*/xmake.lua")
