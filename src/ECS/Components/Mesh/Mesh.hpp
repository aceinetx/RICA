#pragma once
#include "../../../Logger/Logger.hpp"
#include "../../../rica.hpp"
#include "../Component.hpp"
#include <raylib.h>
#include <raymath.h>

class MeshComponent : public Component {
public:
  MeshComponent() : logger(Log::getInstance()) {};

  ~MeshComponent() override {
    if (loaded) {
      UnloadModel(model);
    }
  }

  // Загружаем модель целиком (правильно для GLTF)
  void loadMesh(const char* path) {
    model = LoadModel(path);

    if (model.meshCount == 0) {
      logger.addLog(
          LogLevel::ERROR, basePath,
          TextFormat("Failed to load mesh: empty meshCount from %s", path),
          "logRica.txt");
      logger.addLog(
          LogLevel::ERROR, basePath,
          TextFormat("Failed to load mesh: empty meshCount from %s", path));
      return;
    }

    loaded = true;
  }

  // Установить глобальный цвет модели
  void setColor(Color newColor) {
    color = newColor;
  }

  Color getColor() const {
    return color;
  }

  Model& getModel() {
    return model;
  }

  bool isLoaded() const {
    return loaded;
  }

private:
  Model model = {0};
  Color color = WHITE;
  bool loaded = false;

protected:
  Log& logger;
};
