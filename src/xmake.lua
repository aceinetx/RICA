target("EngineLib")
	set_kind("static")
	add_files(
		"ECS/**/*.cpp",
		"Engine/*.cpp",
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

	add_packages("raylib", "rapidjson", "fmt", {public=true})
	add_deps("buffered-raylib::buffered-raylib", {public=true})
target_end()
