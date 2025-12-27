#include "Physic.hpp"
#include "../../ECS/Components/Physic/Physic3D/Physic3D.hpp"

Physic3DSystem& physic3DSystem = Physic3DSystem::getInstance();

void Physic3DSystem::update(const std::vector<std::shared_ptr<Entity>>& entities, float dt) {
    for (auto entity : entities) {
        auto physic = entity->getComponent<Physic3DComponent>();
        auto transform = entity->getComponent<Transform3DComponent>();

        if (!physic || !transform || physic->getIsStatic())
            continue;

        Vector3 totalForce = { 0, 0, 0 };

        if (physic->isGravityActive()) {
            totalForce.y += -9.81f * physic->getMass() * physic->getGravityScale();
        }

        for (const auto& f : physic->getForces()) {
            totalForce.x += f.x;
            totalForce.y += f.y;
            totalForce.z += f.z;
        }

        Vector3 acceleration = {
            totalForce.x / physic->getMass(),
            totalForce.y / physic->getMass(),
            totalForce.z / physic->getMass()
        };

        Vector3 currentV = physic->getVelocity();
        currentV.x += acceleration.x * dt;
        currentV.y += acceleration.y * dt;
        currentV.z += acceleration.z * dt;

        currentV.x *= physic->getDamping();
        currentV.y *= physic->getDamping();
        currentV.z *= physic->getDamping();

        physic->setVelocity(currentV);

        Vector3 pos = transform->getPosition();
        pos.x += currentV.x * dt;
        pos.y += currentV.y * dt;
        pos.z += currentV.z * dt;
        transform->setPosition(pos);

        physic->clearForces();
    }
}