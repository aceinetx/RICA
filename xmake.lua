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
add_requires("lua", {external=false})
add_requires("fmt", {external=false})
set_warnings("all") -- warns
set_languages("c++17")

-- yes, luabridge3 exists in xmake-repo
-- the reason it's not used with add_requires
-- is because the last version is from Oct. 23, 2023
-- but we use features that were added after that date
-- - d0cc306 Added newFunction to easily wrap callable lambdas (#161)
-- - f3c8f97 Fix issue with lambdas being incorrectly copied
target("luabridge3")
	set_kind("static")

	add_includedirs("lib/LuaBridge3/Source", {public=true})
target_end()

includes("lib/BufferedRaylib")
includes("xmake/autoformat.lua", "src", "game")
