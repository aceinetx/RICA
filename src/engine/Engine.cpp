#include "Engine.hpp"

#include "../rica.hpp"

#include <fstream>
#include <string> // Добавлен для std::stoi

Engine& Engine::getInstance() {
  static Engine instance;
  return instance;
}

Engine::Engine() : sceneManager(*this), logger(Log::getInstance()) {
}

bool Engine::parseInitFile(rapidjson::Document& doc) {
  std::fstream initFile("initEngine.json");
  if (!initFile.is_open()) {
    logger.addLog(LogLevel::ERROR, "Не удалось открыть файл initEngine.json",
                  "logRica.txt");
    return false;
  }
  std::string initString((std::istreambuf_iterator<char>(initFile)),
                         std::istreambuf_iterator<char>());
  doc.Parse(initString.c_str());
  if (doc.HasParseError()) {
    logger.addLog(LogLevel::ERROR,
                  "Ошибка парсинга JSON на позиции " +
                      std::to_string(doc.GetErrorOffset()),
                  "logRica.txt");
    return false;
  }
  return true;
}

std::optional<Engine::RayLibVar> Engine::parseInitFileForRayLib() {
  RayLibVar rayVar;
  rayVar.flag = 0;
  rapidjson::Document doc;

  if (!parseInitFile(doc))
    return {};

  // Ранний выход, если нет корневого объекта "rayLib"
  if (!doc.HasMember("rayLib") || !doc["rayLib"].IsObject())
    return {};

  const rapidjson::Value& config = doc["rayLib"];

  // 1. Парсинг заголовка и FPS
  if (config.HasMember("windowTitle") && config["windowTitle"].IsString())
    rayVar.title = config["windowTitle"].GetString();
  if (config.HasMember("maxFPS") && config["maxFPS"].IsInt())
    rayVar.maxFPS = config["maxFPS"].GetInt();

  // 2. Парсинг разрешения и флагов
  if (config.HasMember("resolution") && config["resolution"].IsObject()) {
    const rapidjson::Value& resolution = config["resolution"];

    auto parseDimension = [&](const char* key, int& dimension) {
      if (!resolution.HasMember(key))
        return;
      const rapidjson::Value& value = resolution[key];
      if (value.IsInt()) {
        dimension = value.GetInt();
      } else if (value.IsString()) {
        std::string strValue = value.GetString();
      }
    };

    parseDimension("width", rayVar.width);
    parseDimension("height", rayVar.height);

    if (config.HasMember("configurationFlags") &&
        config["configurationFlags"].IsArray()) {
      const rapidjson::Value& flagsArray = config["configurationFlags"];
      for (rapidjson::SizeType i = 0; i < flagsArray.Size(); i++) {
        if (flagsArray[i].IsString()) {
          const char* flagString = flagsArray[i].GetString();
          rayVar.flag += getFlagValue(flagString);
        }
      }
    }
  }

  SetConfigFlags(rayVar.flag);
  InitWindow(rayVar.width, rayVar.height, rayVar.title.c_str());
  SetTargetFPS(rayVar.maxFPS);

  return rayVar;
}

unsigned int Engine::getFlagValue(const char* flagName) {
  if (strcmp(flagName, "FLAG_FULLSCREEN_MODE") == 0)
    return FLAG_FULLSCREEN_MODE;
  if (strcmp(flagName, "FLAG_WINDOW_RESIZABLE") == 0)
    return FLAG_WINDOW_RESIZABLE;
  if (strcmp(flagName, "FLAG_WINDOW_UNDECORATED") == 0)
    return FLAG_WINDOW_UNDECORATED;
  if (strcmp(flagName, "FLAG_WINDOW_HIDDEN") == 0)
    return FLAG_WINDOW_HIDDEN;
  if (strcmp(flagName, "FLAG_WINDOW_MINIMIZED") == 0)
    return FLAG_WINDOW_MINIMIZED;
  if (strcmp(flagName, "FLAG_WINDOW_MAXIMIZED") == 0)
    return FLAG_WINDOW_MAXIMIZED;
  if (strcmp(flagName, "FLAG_WINDOW_UNFOCUSED") == 0)
    return FLAG_WINDOW_UNFOCUSED;
  if (strcmp(flagName, "FLAG_WINDOW_TOPMOST") == 0)
    return FLAG_WINDOW_TOPMOST;
  if (strcmp(flagName, "FLAG_WINDOW_ALWAYS_RUN") == 0)
    return FLAG_WINDOW_ALWAYS_RUN;
  if (strcmp(flagName, "FLAG_WINDOW_TRANSPARENT") == 0)
    return FLAG_WINDOW_TRANSPARENT;

  if (strcmp(flagName, "FLAG_VSYNC_HINT") == 0)
    return FLAG_VSYNC_HINT;
  if (strcmp(flagName, "FLAG_MSAA_4X_HINT") == 0)
    return FLAG_MSAA_4X_HINT;
  if (strcmp(flagName, "FLAG_INTERLACED_HINT") == 0)
    return FLAG_INTERLACED_HINT;
  return 0;
}

bool Engine::init() {
  SetTraceLogLevel(LOG_ALL);
  InitAudioDevice();

  isRunning = true;
  auto var = parseInitFileForRayLib();
  // можно использовать var.has_value(), но лучше оставить так для
  // читабельности
  if (!var)
    return false;
  return true;
}

void Engine::update() {
}

void Engine::deleteAllScenes() {
  sceneManager.scenes.clear();
}

void Engine::shutdown() {
  CloseWindow();
}

void Engine::updateCurrentScene() {
  logger.addLog(LogLevel::DEBUG, "updateCurrentWorld", "logRica.txt");
  auto scene = sceneManager.getActiveScene();
  scene->updateEntity();
}

bool Engine::getIsRunning() {
  return isRunning;
}

void Engine::setIsRunning(bool isRunning) {
  this->isRunning = isRunning;
}

float Engine::getDeltaTime() const {
  return deltaTime;
}
