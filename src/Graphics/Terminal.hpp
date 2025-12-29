#pragma once

#include <cstdint>
#include <string>

/// @brief Easily control the terminal
class Terminal {
public:
  /// @brief Copy constructor
  Terminal(const Terminal&) = delete;
  /// @brief Copy assignment
  Terminal& operator=(const Terminal&) = delete;
  /// @brief Move constructor
  Terminal(Terminal&&) = delete;
  /// @brief Move assignment
  Terminal& operator=(Terminal&&) = delete;

  /// @brief Get the global instance
  static Terminal& getInstance();

  /// @brief Clear the entire terminal
  void clear();

  /// @brief Clear only some area of the terminal
  void clearArea(int startX, int startY, int endX, int endY);

  /// @brief Put a symbol at a certain location
  void put(int x, int y, wchar_t symbol);

  /// @brief Set the foreground color
  void setForegroundColor(uint8_t r, uint8_t g, uint8_t b);

  /// @brief Set the background color
  void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b);

  /// @brief Reset background/foreground color
  void resetColor();

  /// @brief Run a system command
  void runCommand(const std::wstring& command);

  /// @brief Set the cursor position
  void setCursorPosition(int x, int y);

  /// @brief Hide the cursor
  void hideCursor();

  /// @brief Show the cursor
  void showCursor();

  /// @brief Save the cursor state
  void saveCursor();

  /// @brief Restore the cursor state
  void restoreCursor();

  /// @brief Get the terminal size
  void getSize();

private:
  /// @brief Constructor
  Terminal() = default;

  /// @brief Destructor
  ~Terminal();
};
