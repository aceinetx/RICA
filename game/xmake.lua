target("MyGame")
    set_kind("binary")
    add_files("src/*.cpp")

    add_deps("EngineLib")
target_end()
