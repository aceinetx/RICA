#include "Engine.hpp"

#include "../rica.hpp"

#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string> // Добавлен для std::stoi
#include <thread>

// Глобальная переменная движка (Engine Singleton)
Engine& engine = Engine::getInstance();

bool parseInitFile(rapidjson::Document& doc) {
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
unsigned int GetFlagValue(const char* flagName) {

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
struct RayLibVar {
  int width = 200;
  int height = 400;
  const char* title = "Default Game Title";
  int maxFPS = 60;
  unsigned int flag = 0;
};
RayLibVar parseInitFileForRayLib() {
  RayLibVar rayVar;
  rayVar.flag = 0;
  rapidjson::Document doc;

  RayLibVar error = {0, 0, "error", 1, false};

  if (!parseInitFile(doc))
    return error; // Используем вспомогательную функцию

  // Ранний выход, если нет корневого объекта "rayLib"
  if (!doc.HasMember("rayLib") || !doc["rayLib"].IsObject())
    return error;

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
          rayVar.flag += GetFlagValue(flagString);
        }
      }
    }
  }
  SetConfigFlags(rayVar.flag);
  InitWindow(rayVar.width, rayVar.height, rayVar.title);
  SetTargetFPS(rayVar.maxFPS);

  return rayVar;
}

void Engine::init() {
  SetTraceLogLevel(LOG_ALL);
  InitAudioDevice();

  isRunning = true;
  parseInitFileForRayLib();
}
void Engine::update() {
}
void Engine::deleteVectorSceneManager() {
  for (size_t i = 0; i < vectorSceneManager.size(); i++) {
    if (vectorSceneManager[i] != nullptr) {
      delete vectorSceneManager[i];
      vectorSceneManager[i] = nullptr;
    }
  }
}
void Engine::shutdown() {
  CloseWindow();
}

std::vector<Scene*> Engine::vectorSceneManager;
Engine::SceneManager Engine::sceneManager;

void Engine::updateCurrentScene() {
  logger.addLog(LogLevel::DEBUG, "updateCurrentWorld", "logRica.txt");
  unsigned int currentSceneId = sceneManager.getCurrentSceneID();
  if (currentSceneId < vectorSceneManager.size() &&
      vectorSceneManager[currentSceneId] != nullptr) {
    vectorSceneManager[currentSceneId]->updateEntity();
  }
}

Scene& Engine::SceneManager::newSceneByID(unsigned int ID) {
  if (ID >= Engine::vectorSceneManager.size()) {
    logger.addLog(LogLevel::WARNING,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.",
                  "logRica.txt");
    Engine::vectorSceneManager.resize(ID + 1, nullptr);
  }
  if (Engine::vectorSceneManager[ID] != nullptr) {
    delete Engine::vectorSceneManager[ID];
  }
  Scene* scenePtr = new Scene();
  Engine::vectorSceneManager[ID] = scenePtr;
  return *scenePtr;
}

void Engine::SceneManager::setSceneByID(unsigned int ID) {
  if (ID >= vectorSceneManager.size()) {
    logger.addLog(LogLevel::WARNING,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": out of bounds",
                  "logRica.txt");
    return;
  }
  if (vectorSceneManager[ID] == nullptr) {
    logger.addLog(LogLevel::WARNING,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": scene is null",
                  "logRica.txt");
    return;
  }
  sceneCurrent = ID;
}

void Engine::SceneManager::setSceneLimit(unsigned int limit) {
  if (limit > Engine::vectorSceneManager.size()) {
    Engine::vectorSceneManager.resize(limit, nullptr);
  } else if (limit < Engine::vectorSceneManager.size()) {
    for (int i = limit; i < (int)Engine::vectorSceneManager.size(); i++) {
      if (Engine::vectorSceneManager[i] != nullptr) {
        delete Engine::vectorSceneManager[i];
        Engine::vectorSceneManager[i] = nullptr;
      }
    }
    Engine::vectorSceneManager.resize(limit);
  }
}

int main() {
  logger.addLog(LogLevel::DEBUG, "main", "logRica.txt");

  gameStart();

  while (engine.getIsRunning() && !WindowShouldClose()) {
    engine.deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_ESCAPE))
      engine.setIsRunning(false);

    unsigned int currentSceneId = engine.sceneManager.getCurrentSceneID();
    if (currentSceneId >= Engine::vectorSceneManager.size() ||
        Engine::vectorSceneManager[currentSceneId] == nullptr) {
      logger.addLog(LogLevel::ERROR, "Invalid scene in main loop",
                    "logRica.txt");
      break;
    }

    Scene* currentScenePtr = Engine::vectorSceneManager[currentSceneId];

    currentScenePtr->OnUpdate(GetFrameTime());
    collider2DSystem.update(currentScenePtr->getAllEntities());
    audioSystem.update(currentScenePtr->getAllEntities());

    BeginDrawing();
    ClearBackground(BLACK);
    renderSystem.update(currentScenePtr->getAllEntities());
    EndDrawing();

    logger.addLog(LogLevel::DEBUG, "gameLoop", "logRica.txt");
    engine.update();
  }

  engine.shutdown();
  return 0;
}