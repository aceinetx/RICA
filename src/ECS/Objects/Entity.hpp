#pragma once
#include "../../Object/Object.hpp"
#include "../../Object/ObjectVector.hpp"

#include <memory>
#include <optional>
#include <string>
#include <vector>

struct Component;

class Entity : public Object {
public:
  Entity();
  Entity(std::string tag);
  virtual ~Entity();

  virtual void Start() {
  }
  virtual void update(float deltaTime) {
  }

  void addComponent(Component* comp);
  template <typename T> T* getComponent();

  int getID() const;

  void setTag(std::string tag) {
    this->tag = tag;
  }
  std::string getTag() {
    return tag;
  }

private:
  ObjectVector<Component*> components;
  int id;
  std::string tag;
};

#include "Entity.inl"
