target("EngineBindings")
	set_kind("static")
	add_rules("swig.cpp", {moduletype="lua"})

	add_files(
		"Lua/*.i"
	)

	add_includedirs(
		".",
		"../lib/BufferedRaylib/src/" -- need to do this explicitly because xmake
	)

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
		"Input/*.cpp"
	)

	add_includedirs(
		".",
		{public=true}
	)

	add_deps("buffered-raylib::buffered-raylib", {public=true})
	add_packages("raylib", "rapidjson", "lua", "swig", {public=true})
target_end()
