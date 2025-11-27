#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

class Component;

class Entity {
public:
  Entity();
  Entity(std::string tag);
  virtual ~Entity();

  virtual void Start() {
  }
  virtual void update(float deltaTime) {
  }

  void addComponent(std::shared_ptr<Component> comp);
  template <typename T> std::shared_ptr<T> getComponent();

  int getID() const;

  void setTag(std::string tag) {
    this->tag = tag;
  }
  std::string getTag() {
    return tag;
  }

private:
  std::vector<std::shared_ptr<Component>> components;
  int id;
  std::string tag;
};

#include "Entity.inl"