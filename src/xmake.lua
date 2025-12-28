target("EngineBindings")
	add_rules("swig.cpp", {moduletype="lua"})

	add_files(
		"Lua/*.i"
	)

	add_includedirs(
		"."
		-- "../lib/BufferedRaylib/src/" -- need to do this explicitly because xmake
	)

	on_load(function (target)
		if not target:is_plat("windows", "mingw")  then
			target:set("prefixname", "lib")
		end
	end)

	add_deps("buffered-raylib::buffered-raylib", {public=true})
	add_packages("lua", {public=true})
target_end()

target("EngineLib")
	set_kind("static")

	add_files(
		"Audio/*.cpp",
		"Collider/**/*.cpp",
		"ECS/**/*.cpp",
		"Engine/*.cpp",
		"Graphics/**/*.cpp",
		"Logger/*.cpp",
		"Physic/**/*.cpp",
		"Scene/*.cpp",
		"UI/*.cpp",
		"Var/*.cpp",
		"Object/*.cpp",
		"Input/*.cpp",
		"main.cpp"
	)

	add_includedirs(
		".",
		{public=true}
	)

	add_deps("EngineBindings", "buffered-raylib::buffered-raylib", {public=true})
	add_packages("raylib", "rapidjson", "fmt", "lua", "swig", {public=true})
target_end()
