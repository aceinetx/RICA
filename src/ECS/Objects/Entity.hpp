#pragma once

#include <string>
#include <utility>
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

  template <typename T, typename... Args> T& AddComponent(Args... args);

  template <typename T> T* GetComponent();

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
  std::vector<Component*> components;
  int id;
  std::string tag;
};

#include "Entity.inl"