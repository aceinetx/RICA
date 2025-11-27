#include "../rica.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

AudioSystem& audioSystem = AudioSystem::getInstance();

void AudioSystem::update(const std::vector<Entity*>& entities) {
  logger.addLog(LogLevel::DEBUG, __FILE__, __func__, "logRica.txt");

  Camera2DComponent* cameraActive = nullptr;
  TransformComponent* transformActive = nullptr;

  for (Entity* entity : entities) {
    Camera2DComponent* camera = entity->getComponent<Camera2DComponent>();
    TransformComponent* transform = entity->getComponent<TransformComponent>();

    if (camera && camera->isActiveCamera() && transform) {
      cameraActive = camera;
      transformActive = transform;
      break;
    }
  }

  for (Entity* entity : entities) {
    TransformComponent* transform = entity->getComponent<TransformComponent>();
    AudioComponent* audio = entity->getComponent<AudioComponent>();

    if (!transform || !audio)
      continue;

    if (cameraActive != nullptr && transformActive != nullptr) {
      float dx = transformActive->getPosition().x - transform->getPosition().x;
      float dy = transformActive->getPosition().y - transform->getPosition().y;

      float l = sqrt(dx * dx + dy * dy);

      float l1_max = sqrt((GetMonitorWidth(0) * GetMonitorWidth(0)) +
                          (GetMonitorHeight(0) * GetMonitorHeight(0)));

      if (l1_max > 0.0f) {
        float normalized_distance = l / l1_max;

        float volume = 1.0f - normalized_distance;

        if (volume < 0.0f) {
          volume = 0.0f;
        }

        audio->setVolumeAll(volume);
      }

      float deltax =
          transform->getPosition().x - transformActive->getPosition().x;
      float clamped_value =
          std::clamp(deltax / GetMonitorWidth(0), -1.0f, 1.0f);
      float pan_value = (1.0f - clamped_value) / 2.0f;
      audio->setPanAll(pan_value);
    }
  }
}