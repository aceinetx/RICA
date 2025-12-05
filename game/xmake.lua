target("MyGame")
    set_kind("binary")
    add_files("*.cpp")

    add_deps("EngineLib")

    add_packages("raylib", "rapidjson")
target_end()
