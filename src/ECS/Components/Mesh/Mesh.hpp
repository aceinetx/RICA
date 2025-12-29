#pragma once
#include "ECS/Components/Component.hpp"
#include <raylib.h>
#include <raymath.h>

/// @brief Provides meshes
class MeshComponent : public Component {
public:
  /// @brief Constructor
  MeshComponent() = default;

  /// @brief Destructor
  ~MeshComponent() override;

  /// @brief Load a mesh from a path
  void loadMesh(const char* path);

  /// @brief Set the meshes color
  void setColor(Color newColor);

  /// @brief Get the meshes color
  Color getColor() const;

  /// @brief Get the mesh model raylib resource
  Model& getModel();

  /// @brief Is the mesh loaded?
  bool isLoaded() const;

private:
  /// @brief Raylib's model resource
  Model model = {{0}};
  /// @brief Mesh color
  Color color = WHITE;
  /// @brief Is loaded?
  bool loaded = false;
};
