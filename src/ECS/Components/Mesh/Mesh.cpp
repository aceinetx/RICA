#include "Mesh.hpp"
MeshComponent::MeshComponent() : logger(Log::getInstance()) {};

MeshComponent::~MeshComponent() {
  if (loaded) {
    UnloadModel(model);
  }
}

void MeshComponent::loadMesh(const char* path) {
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

void MeshComponent::setColor(Color newColor) {
  color = newColor;
}

Color MeshComponent::getColor() const {
  return color;
}

Model& MeshComponent::getModel() {
  return model;
}

bool MeshComponent::isLoaded() const {
  return loaded;
}
