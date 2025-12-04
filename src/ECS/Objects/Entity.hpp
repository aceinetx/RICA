#pragma once

#include <memory>
#include <string>
#include <vector>

struct Component;

class Entity {
public:
  Entity();
  Entity(std::string&& tag);
  virtual ~Entity();

  virtual void start();
  virtual void update(float deltaTime);

  void addComponent(std::shared_ptr<Component> comp);
  template <typename T> std::shared_ptr<T> getComponent();

  [[nodiscard]] int getID() const;

  void setTag(std::string tag);
  std::string getTag();

private:
  std::vector<std::shared_ptr<Component>> components;
  int id;
  std::string tag;
};
