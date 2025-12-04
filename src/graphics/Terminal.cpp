#include "Terminal.hpp"

Terminal& Terminal::getInstance() {
  static Terminal instance;
  return instance;
}

Terminal::~Terminal() {
  // Восстанавливаем настройки при разрушении
  resetColor();
  showCursor();
  fflush(stdout);
}

void Terminal::clear() {
  wprintf(L"\033[2J\033[H");
  fflush(stdout);
}

void Terminal::clearArea(int startX, int startY, int endX, int endY) {
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

void Terminal::put(int x, int y, wchar_t symbol) {
  wprintf(L"\033[%d;%dH%lc", y + 1, x + 1, symbol);
  fflush(stdout);
}

void Terminal::setForegroundColor(uint8_t r, uint8_t g, uint8_t b) {
  wprintf(L"\033[38;2;%d;%d;%dm", r, g, b);
  fflush(stdout);
}

void Terminal::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b) {
  wprintf(L"\033[48;2;%d;%d;%dm", r, g, b);
  fflush(stdout);
}

void Terminal::resetColor() {
  wprintf(L"\033[0m");
  fflush(stdout);
}

void Terminal::runCommand(const std::wstring& command) {
  wprintf(L"%ls", command.c_str());
  fflush(stdout);
}

void Terminal::setCursorPosition(int x, int y) {
  wprintf(L"\033[%d;%dH", y, x);
  fflush(stdout);
}

void Terminal::hideCursor() {
  wprintf(L"\033[?25l");
  fflush(stdout);
}

void Terminal::showCursor() {
  wprintf(L"\033[?25h");
  fflush(stdout);
}

void Terminal::saveCursor() {
  wprintf(L"\033[s");
  fflush(stdout);
}

void Terminal::restoreCursor() {
  wprintf(L"\033[u");
  fflush(stdout);
}

void Terminal::getSize() {
}
