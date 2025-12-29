#pragma once
#include "Object/Object.hpp"
#include "Object/ObjectVector.hpp"

#include <cassert>
#include <string>

struct Component;

/// @brief Base class for all entities
class Entity : public Object {
public:
  /// @brief Constructor
  Entity();
  /// @brief Constructor
  Entity(std::string tag);
  /// @brief Virtual Destructor
  virtual ~Entity();

  /// @brief Start
  virtual void Start();
  /// @brief Function called on every frame
  /// @param deltaTime Frames delta time
  virtual void update(float deltaTime);

  /// @brief Add a component to this entity
  void addComponent(Component* comp);
  /// @brief Get a component by it's type
  /// @return The component, nullptr if entity does not have it
  template <typename T> T* getComponent() {
    for (auto componentPtr : components) {
      assert(componentPtr);

      if (auto casted = dynamic_cast<T*>(componentPtr)) {
        return casted;
      }
    }
    return nullptr;
  }

  /// @brief Get the entity's global ID
  int getID() const;

  /// @brief Set the entity's tag
  void setTag(std::string tag);
  /// @brief Get the entity's tag
  std::string getTag();

private:
  /// @brief Entity components
  ObjectVector<Component*> components;
  /// @brief Global ID
  int id;
  /// @brief Entity tag
  std::string tag;
};
