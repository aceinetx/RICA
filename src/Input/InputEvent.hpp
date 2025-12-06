#pragma once
#include <raylib.h>

enum class InputEventType {
  Keyboard,
};

struct InputEvent {
  union {
    struct {
      KeyboardKey key;
      bool isDown;
    } keyboard;

    struct {
      float delta;
    } mouse_wheel;

    struct {
      MouseButton button;
      bool isDown;
    } mouse_button;

    struct {
      Vector2 position;
    } mouse_position;
  };

  InputEventType type;
};