#include "Audio/Audio.hpp"
#include "rica.hpp"

int main() {
  Log& logger = Log::getInstance();
  logger.addLog(LogLevel::DEBUG, "main", "logRica.txt");

  Engine& engine = Engine::getInstance();
  SceneManager& sceneManager = engine.sceneManager;
  RenderSystem& renderSystem = RenderSystem::getInstance();
  Collider2DSystem& collider2DSystem = Collider2DSystem::getInstance();
  AudioSystem& audioSystem = AudioSystem::getInstance();

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