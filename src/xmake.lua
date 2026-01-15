target("box2cpp")
	set_kind("headeronly")

	add_includedirs("../lib/box2cpp/include", {public=true})
target_end()

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

	add_packages("raylib", "rapidjson", "fmt", "box2d", {public=true})
	add_deps("buffered-raylib::buffered-raylib", "box2cpp", {public=true})
target_end()
