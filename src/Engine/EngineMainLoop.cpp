#include "rica.hpp"

void Engine::mainLoop() {
  static auto& audioSystem = AudioSystem::getInstance();
  static auto& collider2DSystem = Collider2DSystem::getInstance();
  static auto& render3Dsystem = Render3DSystem::getInstance();
  static auto& render2Dsystem = Render2DSystem::getInstance();
  static auto& physic3DSystem = Physic3DSystem::getInstance();

  while (getIsRunning() && !WindowShouldClose()) {
    m_deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_ESCAPE)) {
      setIsRunning(false);
      break;
    }

    m_input.PollEvents();

    // 1. ОБНОВЛЕНИЕ ЛОГИКИ СЦЕНЫ
    sceneManager.updateCurrentScene(GetFrameTime());

    // ==========================================================
    // 2. OFF-SCREEN РЕНДЕРИНГ (Заполнение текстур)
    //    Этот блок должен быть ВНЕ BeginDrawing()/EndDrawing()
    // ==========================================================
    auto currentScene = sceneManager.getCurrentScene();
    if (currentScene) {
      if (is3Dmode()) {
        render3Dsystem.update(currentScene->getAllEntities());
        physic3DSystem.update(currentScene->getAllEntities(), m_deltaTime);
      } else {
        collider2DSystem.update(currentScene->getAllEntities());
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
    RenderTexture2D& targetTexture = is3Dmode()
                                         ? render3Dsystem.getRenderTexture()
                                         : render2Dsystem.getRenderTexture();

    int width =
        is3Dmode() ? render3Dsystem.getWidth() : render2Dsystem.getWidth();
    int height =
        is3Dmode() ? render3Dsystem.getHeight() : render2Dsystem.getHeight();

    // Финальная отрисовка буфера на экран (здесь можно добавить шейдер)
    if (targetTexture.id > 0) {
      if (m_shader)
        BeginShaderMode(m_shader->getRaylibShader());

      DrawTextureRec(targetTexture.texture,
                     // Используем правильные размеры и отрицательную высоту
                     (Rectangle){0, 0, (float)width, (float)-height},
                     (Vector2){0, 0}, WHITE);

      if (m_shader)
        EndShaderMode();
    } else {
      rica::log::error("Main loop", "targetTexture.id > 0 failed");
    }

    // Отрисовка UI/FPS поверх сцены
    DrawFPS(10, 10);

    EndDrawing(); // <-- ЗАКРЫВАЕМ БЛОК ОТРИСОВКИ НА ЭКРАН

    update();
  }

  shutdown();
}
