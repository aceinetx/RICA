#pragma once
#include "ECS/Components/Component.hpp"
#include <raylib.h>
#include <raymath.h>

class MeshComponent : public Component {
public:
  MeshComponent() = default;

  ~MeshComponent() override;

  // Загружаем модель целиком (правильно для GLTF)
  void loadMesh(const char* path);

  // Установить глобальный цвет модели
  void setColor(Color newColor);

  Color getColor() const;

  Model& getModel();

  bool isLoaded() const;

private:
  Model model = {{0}};
  Color color = WHITE;
  bool loaded = false;
};
