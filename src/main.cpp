#include "rica.hpp"

int main() {
  if (!gameStart())
    return 1;

  static auto& audioSystem = AudioSystem::getInstance();
  static auto& physics2DSystem = Physics2DSystem::getInstance();
  static auto& engine = Engine::getInstance();
  static auto& render3Dsystem = Render3DSystem::getInstance();
  static auto& render2Dsystem = Render2DSystem::getInstance();
  static auto& physic3DSystem = Physic3DSystem::getInstance();

  while (engine.getIsRunning() && !WindowShouldClose()) {
    engine.m_deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_ESCAPE)) {
      engine.setIsRunning(false);
      break;
    }

    engine.m_input.PollEvents();

    // 1. ОБНОВЛЕНИЕ ЛОГИКИ СЦЕНЫ
    engine.sceneManager.updateCurrentScene(GetFrameTime());

    // ==========================================================
    // 2. OFF-SCREEN РЕНДЕРИНГ (Заполнение текстур)
    //    Этот блок должен быть ВНЕ BeginDrawing()/EndDrawing()
    // ==========================================================
    auto currentScene = engine.sceneManager.getCurrentScene();
    if (currentScene) {
      if (engine.is3Dmode()) {
        render3Dsystem.update(currentScene->getAllEntities());
        physic3DSystem.update(currentScene->getAllEntities(),
                              engine.m_deltaTime);
      } else {
        physics2DSystem.update(currentScene->getAllEntities());
        render2Dsystem.update(currentScene->getAllEntities());
      }
      audioSystem.update(currentScene->getAllEntities());
    } else {
      rica::log::error("main", "currentScene == nullptr");
    }

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
      if (engine.m_shader)
        BeginShaderMode(engine.m_shader->getRaylibShader());

      DrawTextureRec(targetTexture.texture,
                     // Используем правильные размеры и отрицательную высоту
                     (Rectangle){0, 0, (float)width, (float)-height},
                     (Vector2){0, 0}, WHITE);

      if (engine.m_shader)
        EndShaderMode();
    } else {
      rica::log::error("Main loop", "targetTexture.id > 0 failed");
    }

    // Отрисовка UI/FPS поверх сцены
    DrawFPS(10, 10);

    EndDrawing(); // <-- ЗАКРЫВАЕМ БЛОК ОТРИСОВКИ НА ЭКРАН

    engine.update();
  }

  engine.shutdown();
  return 0;
}
