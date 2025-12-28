#pragma once
#include <ECS/Components/Mesh/Mesh.hpp>
#include <ECS/Components/Transform/Transform3D/Transform3D.hpp>
#include <ECS/Objects/Entity.hpp>
#include <Object/Rc.hpp>

class Player : public Entity {
private:
  float speed = 5.0f;
  float rotationSpeed = 90.0f;

  Rc<MeshComponent> mesh;
  Rc<Transform3DComponent> trans;

public:
  Player();

  void update(float deltaTime);
};
