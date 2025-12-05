#include "Engine.hpp"

#include "../rica.hpp"
#include "Var/Var.hpp"

#include <fstream>
#include <string> // Добавлен для std::stoi

Engine& Engine::getInstance() {
  static Engine instance;
  return instance;
}

Engine::Engine() : sceneManager(*this), logger(Log::getInstance()) {
}

void Engine::update() {
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

bool Engine::getIsRunning() {
  return isRunning;
}

void Engine::setIsRunning(bool isRunning) {
  this->isRunning = isRunning;
}

void Engine::deleteAllScenes() {
  sceneManager.scenes.clear();
}

void Engine::shutdown() {
  CloseWindow();
}

float Engine::getDeltaTime() const {
  return deltaTime;
}

void Engine::set3Dmode(const bool& is3D) {
  this->is3D = is3D;
}

bool Engine::is3Dmode() const {
  return is3D;
}

void Engine::deleteVectorSceneManager() {
  sceneManager.scenes.clear();
}

void Engine::updateCurrentScene() {
  logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");

  auto currentScenePtr = sceneManager.getActiveScene();
  currentScenePtr->updateEntity();
}

bool Engine::parseInitFile(rapidjson::Document& doc) {
  std::fstream initFile("initEngine.json");
  if (!initFile.is_open()) {
    logger.addLog(LogLevel::ERROR, basePath, "Failed to load initEngine.json",
                  "logRica.txt");
    logger.addLog(LogLevel::ERROR, basePath, "Failed to load initEngine.json");

    return false;
  }

  std::string initString((std::istreambuf_iterator<char>(initFile)),
                         std::istreambuf_iterator<char>());
  doc.Parse(initString.c_str());

  if (doc.HasParseError()) {
    logger.addLog(LogLevel::ERROR, basePath,
                  "Failed to parse JSON for position" +
                      std::to_string(doc.GetErrorOffset()),
                  "logRica.txt");
    logger.addLog(LogLevel::ERROR, basePath,
                  "Failed to parse JSON for position" +
                      std::to_string(doc.GetErrorOffset()));

    return false;
  }
  return true;
}

std::optional<RayLibVar> Engine::parseInitFileForRayLib() {
  RayLibVar rayVar;
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

unsigned int Engine::getFlagValue(std::string flagName) {
  if (flagName == "FLAG_FULLSCREEN_MODE")
    return FLAG_FULLSCREEN_MODE;
  if (flagName == "FLAG_WINDOW_RESIZABLE")
    return FLAG_WINDOW_RESIZABLE;
  if (flagName == "FLAG_WINDOW_UNDECORATED")
    return FLAG_WINDOW_UNDECORATED;
  if (flagName == "FLAG_WINDOW_HIDDEN")
    return FLAG_WINDOW_HIDDEN;
  if (flagName == "FLAG_WINDOW_MINIMIZED")
    return FLAG_WINDOW_MINIMIZED;
  if (flagName == "FLAG_WINDOW_MAXIMIZED")
    return FLAG_WINDOW_MAXIMIZED;
  if (flagName == "FLAG_WINDOW_UNFOCUSED")
    return FLAG_WINDOW_UNFOCUSED;
  if (flagName == "FLAG_WINDOW_TOPMOST")
    return FLAG_WINDOW_TOPMOST;
  if (flagName == "FLAG_WINDOW_ALWAYS_RUN")
    return FLAG_WINDOW_ALWAYS_RUN;
  if (flagName == "FLAG_WINDOW_TRANSPARENT")
    return FLAG_WINDOW_TRANSPARENT;
  if (flagName == "FLAG_VSYNC_HINT")
    return FLAG_VSYNC_HINT;
  if (flagName == "FLAG_MSAA_4X_HINT")
    return FLAG_MSAA_4X_HINT;
  if (flagName == "FLAG_INTERLACED_HINT")
    return FLAG_INTERLACED_HINT;
  std::abort();
}