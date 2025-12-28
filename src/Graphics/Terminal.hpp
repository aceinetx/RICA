#pragma once

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

class Terminal {
public:
  // Паттерн Singleton
  Terminal(const Terminal&) = delete;
  Terminal& operator=(const Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal& operator=(Terminal&&) = delete;

  static Terminal& getInstance() {
    static Terminal instance;
    return instance;
  }

  // Публичные методы
  void clear() {
    wprintf(L"\033[2J\033[H");
    fflush(stdout);
  }

  void clearArea(int startX, int startY, int endX, int endY) {
    wprintf(L"\033[s");
    fflush(stdout);

    for (int y = startY; y <= endY; y++) {
      wprintf(L"\033[%d;%dH", y, startX);
      int count = endX - startX + 1;
      if (count > 0) {
        wprintf(L"\033[%dX", count);
      }
      fflush(stdout);
    }

    wprintf(L"\033[u");
    fflush(stdout);
  }

  void put(int x, int y, wchar_t symbol) {
    wprintf(L"\033[%d;%dH%lc", y + 1, x + 1, symbol);
    fflush(stdout);
  }

  void setForegroundColor(uint8_t r, uint8_t g, uint8_t b) {
    wprintf(L"\033[38;2;%d;%d;%dm", r, g, b);
    fflush(stdout);
  }

  void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b) {
    wprintf(L"\033[48;2;%d;%d;%dm", r, g, b);
    fflush(stdout);
  }

  void resetColor() {
    wprintf(L"\033[0m");
    fflush(stdout);
  }

  void runCommand(const std::wstring& command) {
    wprintf(L"%ls", command.c_str());
    fflush(stdout);
  }

  void setCursorPosition(int x, int y) {
    wprintf(L"\033[%d;%dH", y, x);
    fflush(stdout);
  }

  void hideCursor() {
    wprintf(L"\033[?25l");
    fflush(stdout);
  }

  void showCursor() {
    wprintf(L"\033[?25h");
    fflush(stdout);
  }

  void saveCursor() {
    wprintf(L"\033[s");
    fflush(stdout);
  }

  void restoreCursor() {
    wprintf(L"\033[u");
    fflush(stdout);
  }

  // Получить размер терминала
  void getSize() {
  }

private:
  Terminal() = default;
  ~Terminal() {
    // Восстанавливаем настройки при разрушении
    resetColor();
    showCursor();
    fflush(stdout);
  }
};

// Глобальная ссылка для удобства
extern Terminal& terminal;