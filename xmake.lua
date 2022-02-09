set_project "CryMP-Client"
set_version ("12.0.0", {build = "%Y%m%d%H%M"})

-- compiler languages
set_languages "cxx17"

-- SSE (need tests)
-- add_vectorexts("sse", "sse2", "sse3", "ssse3")

-- packages
add_requires "lua v5.1.5"
add_requires "nlohmann_json"

-- rules
add_rules ("mode.release", "mode.debug")
add_rules ("plugin.vsxmake.autoupdate")

if is_mode("debug") then
    add_defines "DEVELOPER"
end

-- architecture
if is_arch("x86", "i386") then
    add_defines "BUILD_32BIT"
elseif is_arch("x64", "x86_64") then
    add_defines "BUILD_64BIT"
end

-- platform specific
if is_plat("windows") then
    add_ldflags "/DYNAMICBASE:NO"
    if is_arch("x86", "i386") then
    	add_ldflags "/LARGEADDRESSAWARE"
    end
end

-- output
if is_arch("x86", "i386") then
	set_targetdir "$(projectdir)/../Bin32"
else
	set_targetdir "$(projectdir)/../Bin64"
end

-- build config
set_configdir "Code"
add_configfiles "config.h.in"

target "CryMP-Client"
	set_kind "binary"

	-- name
	if is_arch("x86", "i386") then
	    set_basename "CryMP-Client32"
	else
	    set_basename "CryMP-Client64"
	end

	-- common
	add_includedirs "Code"
	add_headerfiles "Code/CryCommon/**.h"
	add_files "Code/CryCommon/CryCore/MTPseudoRandom.cpp"

	-- external
	add_includedirs "Code/Library/External"
	add_files "Code/Library/External/miniz/miniz.c"

	-- launcher
	add_files "Code/Client/*.cpp"
	add_files "Code/Launcher/*.cpp"
	add_files "Resources/*.rc"
	add_files "Resources/*.manifest"

	-- game
	add_files "Code/CryGame/**.cpp"
	add_files "Code/CryScriptSystem/LuaLibs/bitlib.c"
	add_files "Code/CryScriptSystem/**.cpp"

	-- utils
	add_files "Code/Library/*.cpp"

	-- packages
	add_packages ("lua", "nlohmann_json")

	-- system links
	add_syslinks ("user32", "advapi32", "gdi32", "ws2_32", "winhttp")