target("rica-game")
    set_kind("binary")

    add_files(
        "src/main.cpp", 
        "src/Scenes/GameScene.cpp"
    )

    add_deps("EngineLib")

    add_packages("raylib", "rapidjson")

    add_includedirs("..")
target_end()
