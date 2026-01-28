target("rlImGui")
		set_kind("static")

		add_files(
				"../lib/rlImGui/*.cpp"
		)

		add_includedirs("../lib/rlImGui", {public=true})

		add_packages("imgui", {public=true})
target_end()

target("EngineLib")
    set_kind("static")
    add_files(
        "Audio/*.cpp",
        "Collider/**/*.cpp",
        "ECS/**/*.cpp",
        "engine/*.cpp",
        "graphics/**/*.cpp",
        "Logger/*.cpp",
        "Physic/**/*.cpp",
        "Scene/*.cpp",
        "UI/*.cpp",
        "Var/*.cpp"
    )

    add_includedirs(
        ".",
        "ECS/Components/",
        "ECS/Components/Audio/",
        "ECS/Components/Camera/",
        "ECS/Components/Collider/Collider2D/",
        "ECS/Components/Physic/",
        "ECS/Components/Sprite/",
        "ECS/Components/Transform/",
        "ECS/Objects/",
        "ECS/Systems/",
        "Collider/",
        "Collider/Collider2D/",
        "engine/",
        "graphics/",
        "Logger/",
        "Scene/",
        "UI/"
    )

    add_packages("raylib", "rapidjson", "imgui", {public=true})
		add_deps("rlImGui", {public=true})
target_end()
