target("EngineBindings")
	set_kind("static")
	add_rules("swig.cpp", {moduletype="lua"})

	add_files(
		"Lua/*.i"
	)

	add_includedirs(
		".",
		"../lib/BufferedRaylib/src/"
	)

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
		"../lib/BufferedRaylib/src/*.cpp"
	)

	add_includedirs(
		".",
		"../lib/BufferedRaylib/src/",
		{public=true}
	)

	add_packages("raylib", "rapidjson", "lua", "swig")
target_end()
