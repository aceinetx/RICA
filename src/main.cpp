#include "rica.hpp"

int main() {
  Log& logger = Log::getInstance();
  logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");

  Engine& engine = Engine::getInstance();
  SceneManager& sceneManager = engine.sceneManager;
  Collider2DSystem& collider2DSystem = Collider2DSystem::getInstance();
  AudioSystem& audioSystem = AudioSystem::getInstance();
  Render2DSystem& render2Dsystem = Render2DSystem::getInstance();
  Render3DSystem& render3Dsystem = Render3DSystem::getInstance();

  if (!gameStart())
    return 1;

  while (engine.getIsRunning() && !WindowShouldClose()) {
    engine.deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_ESCAPE))
      engine.setIsRunning(false);

    auto currentScenePtr = sceneManager.getActiveScene();
    if (currentScenePtr == nullptr) {
      logger.addLog(LogLevel::ERROR, "Invalid scene in main loop",
                    "logRica.txt");
      break;
    }

    currentScenePtr->onUpdate(GetFrameTime());

    BeginDrawing();
    ClearBackground(BLACK);
    if (engine.is3Dmode()) {
      render3Dsystem.update(currentScenePtr->getAllEntities());
    } else {
      collider2DSystem.update(currentScenePtr->getAllEntities());
      render2Dsystem.update(currentScenePtr->getAllEntities());
      audioSystem.update(currentScenePtr->getAllEntities());
    }
    EndDrawing();

    logger.addLog(LogLevel::DEBUG, basePath, __func__, "logRica.txt");
    engine.update();
  }

  engine.shutdown();
  return 0;
}