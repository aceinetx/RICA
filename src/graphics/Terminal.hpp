#pragma once

#include <cstdint>
#include <string>

class Terminal {
public:
  // Паттерн Singleton
  Terminal(const Terminal&) = delete;
  Terminal& operator=(const Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal& operator=(Terminal&&) = delete;

  static Terminal& getInstance();

  // Публичные методы
  void clear();

  void clearArea(int startX, int startY, int endX, int endY);

  void put(int x, int y, wchar_t symbol);

  void setForegroundColor(uint8_t r, uint8_t g, uint8_t b);

  void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b);

  void resetColor();

  void runCommand(const std::wstring& command);

  void setCursorPosition(int x, int y);

  void hideCursor();

  void showCursor();

  void saveCursor();

  void restoreCursor();

  // Получить размер терминала
  void getSize();

private:
  Terminal() = default;
  ~Terminal();
};