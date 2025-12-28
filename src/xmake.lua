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

	add_packages("raylib", "rapidjson")
	add_deps("buffered-raylib::buffered-raylib", {public=true})
target_end()
