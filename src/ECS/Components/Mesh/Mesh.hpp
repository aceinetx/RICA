#pragma once
#include "../../../Logger/Logger.hpp"
#include "../../../rica.hpp"
#include "../Component.hpp"
#include <raylib.h>
#include <raymath.h>

class MeshComponent : public Component {
public:
  MeshComponent();

  ~MeshComponent() override;

  // Загружаем модель целиком (правильно для GLTF)
  void loadMesh(const char* path);

  // Установить глобальный цвет модели
  void setColor(Color newColor);

  [[nodiscard]] Color getColor() const;

  Model& getModel();

  [[nodiscard]] bool isLoaded() const;

private:
  Model model = {{0}};
  Color color = WHITE;
  bool loaded = false;

protected:
  Log& logger;
};
