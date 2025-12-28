#include "ECS/Components/Mesh/Mesh.hpp"
#include "Logger/Logger.hpp"

MeshComponent::~MeshComponent() {
  if (loaded) {
    UnloadModel(model);
  }
}

void MeshComponent::loadMesh(const char* path) {
  model = LoadModel(path);

  if (model.meshCount == 0) {
    rica::log::error("MeshComponent",
                     "Failed to load mesh: empty meshCount from {}", path);
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
