#pragma once
#include <vector>
#include <memory>
#include "../../rica.hpp" 

class Physic3DSystem {
public:
    static Physic3DSystem& getInstance() {
        static Physic3DSystem instance;
        return instance;
    }

    void init();

    void update(const std::vector<std::shared_ptr<Entity>>& entities, float dt);

private:
    Physic3DSystem() = default;
    ~Physic3DSystem() = default;

    Physic3DSystem(const Physic3DSystem&) = delete;
    Physic3DSystem& operator=(const Physic3DSystem&) = delete;

    float globalGravity = -9.81f;
};

extern Physic3DSystem& physic3DSystem;