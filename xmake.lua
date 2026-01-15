add_rules("mode.debug", "mode.release", "mode.asan", "mode.lsan")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"}) -- generate compile commands
add_rules("rica.autoformat")
set_policy("build.progress_style", "multirow")

set_policy("build.sanitizer.address", true)
set_policy("build.sanitizer.leak", true)
set_policy("build.sanitizer.undefined", true)

-- libs
add_requires("raylib", {external=false})
add_requires("rapidjson", {external=false})
add_requires("fmt", {external=false})
add_requires("box2d", {external=false})
set_warnings("all") -- warns
set_languages("c++20")

includes("lib/BufferedRaylib")
includes("xmake/autoformat.lua", "src", "game")
