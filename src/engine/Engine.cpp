#include "Engine.hpp"
#include "../Object/PoolManager.hpp"

#include "../rica.hpp"
#include "Input/InputDispatcher.hpp"
#include "Physic/Physic3D/Physic.hpp"
#include "Render2D/Render2D.hpp"
#include "Render3D/Render3D.hpp"
#include "Var/Var.hpp"
#include "raylib.h"
#include <lua.h>

#include <fstream>
#include <iostream>
#include <string> // Добавлен для std::stoi

// Глобальная переменная движка (Engine Singleton)
Engine& engine = Engine::getInstance();

Engine::Engine() {
  input.keyboard_callback = CALLBACK_2(Engine::keyboardCallback, this);
  input.mouse_button_callback = CALLBACK_2(Engine::mouseButtonCallback, this);
  input.mouse_position_callback =
      CALLBACK_2(Engine::mousePositionCallback, this);
}

bool parseInitFile(rapidjson::Document& doc) {
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
  std::string title = "Default Game Title";
  int maxFPS = 60;
  unsigned int flag = 0;
};

std::optional<RayLibVar> parseInitFileForRayLib() {
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
          rayVar.flag += GetFlagValue(flagString);
        }
      }
    }
  }

  SetConfigFlags(rayVar.flag);
  InitWindow(rayVar.width, rayVar.height, rayVar.title.c_str());
  if (engine.is3Dmode())
    render3Dsystem.init(rayVar.width, rayVar.height);
  else
    render2Dsystem.init(rayVar.width, rayVar.height);

  SetTargetFPS(rayVar.maxFPS);

  return rayVar;
}

bool Engine::init() {
  m_inputDispatcher = &InputDispatcher::getInstance();

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
  PoolManager::getInstance().clear();
}

void Engine::deleteVectorSceneManager() {
  vectorSceneManager.clear();
}

void Engine::shutdown() {
  CloseWindow();
  engine.shader = {}; // deletes the shader, unloading it
}

void Engine::luaRunScript(std::string path) {
}

ObjectVector<Scene*> Engine::vectorSceneManager;

Engine::SceneManager Engine::sceneManager;

void Engine::updateCurrentScene() {
  logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");
  unsigned int currentSceneId = sceneManager.getCurrentSceneID();
  if (currentSceneId < vectorSceneManager.size() &&
      vectorSceneManager[currentSceneId] != nullptr) {
    vectorSceneManager[currentSceneId]->updateEntity();
  }
}

/*
Scene* Engine::SceneManager::newSceneByID(unsigned int ID) {
  if (ID >= Engine::vectorSceneManager.size()) {

    logger.addLog(LogLevel::CRITICAL, basePath,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.",
                  "logRica.txt");
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "World ID " + std::to_string(ID) +
                      " is out of bounds! Resizing vector.");

    Engine::vectorSceneManager.resize(ID + 1, nullptr);
  }
  if (Engine::vectorSceneManager[ID] != nullptr) {
    Engine::vectorSceneManager[ID] = nullptr;
  }
  auto scenePtr = make_object<Scene>();
  Engine::vectorSceneManager[ID] = scenePtr;
  return scenePtr;
}
*/

void Engine::SceneManager::setSceneByID(unsigned int ID) {
  if (ID >= vectorSceneManager.size()) {
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": out of bounds",
                  "logRica.txt");
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": out of bounds");
    return;
  }
  if (vectorSceneManager[ID] == nullptr) {
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": scene is null",
                  "logRica.txt");
    logger.addLog(LogLevel::CRITICAL, basePath,
                  "Cannot set scene ID " + std::to_string(ID) +
                      ": scene is null");

    return;
  }
  sceneCurrent = ID;
}

void Engine::SceneManager::setSceneLimit(unsigned int limit) {
  /*
  if (limit > Engine::vectorSceneManager.size()) {
    Engine::vectorSceneManager.resize(limit, nullptr);
  } else if (limit < Engine::vectorSceneManager.size()) {
    for (int i = limit; i < (int)Engine::vectorSceneManager.size(); i++) {
      if (Engine::vectorSceneManager[i] != nullptr) {
        Engine::vectorSceneManager[i] = nullptr;
      }
    }
    Engine::vectorSceneManager.resize(limit);
  }
  */
}

void Engine::mouseButtonCallback(MouseButton button, bool isDown) {
  InputEvent ev;
  ev.type = InputEventType::MouseButton;
  ev.mouse_button.button = button;
  ev.mouse_button.isDown = isDown;
  m_inputDispatcher->dispatchEvent(ev, getActiveScene());
}

void Engine::mousePositionCallback(Vector2 pos, Vector2 delta) {
  InputEvent ev;
  ev.type = InputEventType::MousePosition;
  ev.mouse_position.position = pos;
  ev.mouse_position.delta = delta;
  m_inputDispatcher->dispatchEvent(ev, getActiveScene());
}

void Engine::keyboardCallback(KeyboardKey key, bool isDown) {
  InputEvent ev;
  ev.type = InputEventType::Keyboard;
  ev.keyboard.key = key;
  ev.keyboard.isDown = isDown;
  m_inputDispatcher->dispatchEvent(ev, getActiveScene());
}

int main() {
  logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");

  if (!gameStart())
    return 1;

  while (engine.getIsRunning() && !WindowShouldClose()) {
    engine.deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_ESCAPE)) {
      engine.setIsRunning(false);
      break;
    }

    engine.input.PollEvents();

    unsigned int currentSceneId = engine.sceneManager.getCurrentSceneID();
    if (currentSceneId >= Engine::vectorSceneManager.size() ||
        Engine::vectorSceneManager[currentSceneId] == nullptr) {
      logger.addLog(LogLevel::ERROR, basePath, "Invalid scene in main loop",
                    "logRica.txt");
      logger.addLog(LogLevel::ERROR, basePath, "Invalid scene in main loop");

      break;
    }
    // ... (проверка на валидность сцены) ...
    if (currentSceneId >= Engine::vectorSceneManager.size() ||
        Engine::vectorSceneManager[currentSceneId] == nullptr) {
      logger.addLog(LogLevel::ERROR, basePath, "Invalid scene in main loop",
                    "logRica.txt");
      logger.addLog(LogLevel::ERROR, basePath, "Invalid scene in main loop");

      break;
    }

    auto currentScenePtr = Engine::vectorSceneManager[currentSceneId];

    // 1. ОБНОВЛЕНИЕ ЛОГИКИ СЦЕНЫ
    currentScenePtr->OnUpdate(GetFrameTime());

    // ==========================================================
    // 2. OFF-SCREEN РЕНДЕРИНГ (Заполнение текстур)
    //    Этот блок должен быть ВНЕ BeginDrawing()/EndDrawing()
    // ==========================================================
    if (engine.is3Dmode()) {
      render3Dsystem.update(currentScenePtr->getAllEntities());
      physic3DSystem.update(currentScenePtr->getAllEntities(),
                            engine.deltaTime);
    } else {
      collider2DSystem.update(currentScenePtr->getAllEntities());
      render2Dsystem.update(currentScenePtr->getAllEntities());
    }
    audioSystem.update(currentScenePtr->getAllEntities());

    // ==========================================================
    // 3. ON-SCREEN РЕНДЕРИНГ (Отрисовка на экран)
    // ==========================================================
    BeginDrawing();
    ClearBackground(BLACK);

    // Выбираем, какую текстуру и размеры использовать
    RenderTexture2D& targetTexture = engine.is3Dmode()
                                         ? render3Dsystem.getRenderTexture()
                                         : render2Dsystem.getRenderTexture();

    int width = engine.is3Dmode() ? render3Dsystem.getWidth()
                                  : render2Dsystem.getWidth();
    int height = engine.is3Dmode() ? render3Dsystem.getHeight()
                                   : render2Dsystem.getHeight();

    // Финальная отрисовка буфера на экран (здесь можно добавить шейдер)
    if (targetTexture.id > 0) {
      BeginShaderMode(engine.shader->getRaylibShader());

      DrawTextureRec(targetTexture.texture,
                     // Используем правильные размеры и отрицательную высоту
                     (Rectangle){0, 0, (float)width, (float)-height},
                     (Vector2){0, 0}, WHITE);

      EndShaderMode();
    }

    //

    // Отрисовка UI/FPS поверх сцены
    DrawFPS(10, 10);

    EndDrawing(); // <-- ЗАКРЫВАЕМ БЛОК ОТРИСОВКИ НА ЭКРАН

    logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");
    engine.update();
  }

  engine.shutdown();
  return 0;
}
