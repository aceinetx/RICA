#include "camera_controller.hpp"
#include "player.hpp"
#include "raylib.h"
#include "rica.hpp"

const int screenWidth = 1920;
const int screenHeight = 1080;

class GameScene : public Scene {
private:
  Rc<Player> player;
  Rc<CameraController> cameraEntity;
  Rc<Entity> shaderEntity;

  int timeLoc;
  int resolutionLoc;
  std::array<float, 2> resolution;

public:
  GameScene() {
    static auto& engine = Engine::getInstance();

    cameraEntity = make_rc<CameraController>();
    this->createEntity(cameraEntity);
    player = make_rc<Player>();
    this->createEntity(player);

    auto& engineShader = engine.getShader();

    engineShader = EngineShader({}, "raymarching.fs");

    timeLoc = engineShader->getShaderLocation("time");
    resolutionLoc = engineShader->getShaderLocation("resolution");

    resolution[0] = (float)screenWidth;
    resolution[1] = (float)screenHeight;

    engineShader->setShaderValue(resolutionLoc, resolution);
  }

  ~GameScene() {
  }

  void OnUpdate(float dt) override {
    static auto& engine = Engine::getInstance();
    auto& engineShader = engine.getShader();

    float time = (float)GetTime();
    engineShader->setShaderValue(timeLoc, time);
    if (cameraEntity)
      cameraEntity->update(dt);
  }
};

bool gameStart() {
  static auto& engine = Engine::getInstance();
  static auto& render3Dsystem = Render3DSystem::getInstance();

  engine.set3Dmode(true);
  if (!engine.init())
    return false;

  engine.sceneManager.setSceneLimit(10);
  engine.sceneManager.createScene<GameScene>();

  render3Dsystem.setSkyColor({100, 100, 100, 100});

  return true;
}
