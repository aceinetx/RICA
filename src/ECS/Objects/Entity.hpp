#pragma once
#include "Object/Object.hpp"
#include "Object/ObjectVector.hpp"

#include <cassert>
#include <string>

struct Component;

class Entity : public Object {
public:
  Entity();
  Entity(std::string tag);
  virtual ~Entity();

  virtual void Start();
  virtual void update(float deltaTime);

  void addComponent(Component* comp);
  template <typename T> T* getComponent() {
    for (auto componentPtr : components) {
      assert(componentPtr);

      if (auto casted = dynamic_cast<T*>(componentPtr)) {
        return casted;
      }
    }
    return nullptr;
  }

  int getID() const;

  void setTag(std::string tag);
  std::string getTag();

private:
  ObjectVector<Component*> components;
  int id;
  std::string tag;
};
