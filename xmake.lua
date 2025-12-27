add_rules("mode.debug", "mode.release", "mode.asan", "mode.lsan")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"}) -- generate compile commands
add_rules("rica.autoformat")

set_policy("build.sanitizer.address", true)
set_policy("build.sanitizer.leak", true)
set_policy("build.sanitizer.undefined", true)

-- libs
add_requires("raylib", {external=false})
add_requires("rapidjson", {external=false})
set_warnings("all") -- warns
set_languages("c++17")

includes("lib/BufferedRaylib")
includes("xmake/autoformat.lua", "src", "game")
