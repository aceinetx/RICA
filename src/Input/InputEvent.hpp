#pragma once
#include <raylib.h>

/// @brief All input event types
enum class InputEventType {
  Keyboard,
  MouseWheel,
  MouseButton,
  MousePosition,
};

/// @brief Represents an input event
struct InputEvent {
  /// @brief Unites all event types' data
  union {
    /// @brief Represents a keyboard event
    struct {
      /// @brief Keyboard key
      KeyboardKey key;
      /// @brief Is the key down?
      bool isDown;
    } keyboard;

    /// @brief Represents a mouse wheel event
    struct {
      /// @brief Wheel delta
      float delta;
    } mouse_wheel;

    /// @brief Represents a mouse button event
    struct {
      /// @brief Mouse button
      MouseButton button;
      /// @brief Is the button down?
      bool isDown;
    } mouse_button;

    /// @brief Represents a mouse position event
    struct {
      /// @brief Mouse position
      Vector2 position;
      /// @brief Mouse delta
      Vector2 delta;
    } mouse_position;
  };

  /// @brief The input event type
  InputEventType type;
};
