#include "Python/Bindings.hpp"
#include "rica.hpp"
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace pyb = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, Rc<T>, true);

namespace rica::py::bindings {
  class PyScene : public Scene {
  public:
    using Scene::Scene;

    void onUpdate(float dt) override {
      PYBIND11_OVERLOAD(void, Scene, onUpdate, dt);
    }
  };

  class PyLog {
  public:
    static void debug(std::string module, std::string text) {
      rica::log::debug(module, text);
    }

    static void info(std::string module, std::string text) {
      rica::log::info(module, text);
    }

    static void warning(std::string module, std::string text) {
      rica::log::warning(module, text);
    }

    static void error(std::string module, std::string text) {
      rica::log::error(module, text);
    }

    static void critical(std::string module, std::string text) {
      rica::log::critical(module, text);
    }
  };

  static void bindEngine(pyb::module& m) {
    pyb::class_<Engine, std::unique_ptr<Engine, pyb::nodelete>>(m, "Engine")
        .def_static("getInstance", &Engine::getInstance,
                    pyb::return_value_policy::reference)
        .def("set3Dmode", &Engine::set3Dmode)
        .def("is3Dmode", &Engine::is3Dmode)
        .def("setIsRunning", &Engine::setIsRunning)
        .def("getIsRunning", &Engine::getIsRunning)
        .def("init", &Engine::init)
        .def("shutdown", &Engine::shutdown)
        .def("getDeltaTime", &Engine::getDeltaTime)
        .def("mainLoop", &Engine::mainLoop)
        .def_readwrite("sceneManager", &Engine::sceneManager);
  }

  static void bindObject(pyb::module& m) {
    pyb::class_<Object, Rc<Object>>(m, "Object")
        .def(pyb::init<>())
        .def("autorelease",
             [](Rc<Object> self) { PoolManager::getInstance().add(self); })
        .def("init",
             [](Rc<Object> self) { PoolManager::getInstance().add(self); })
        .def("release", &Object::retain)
        .def("retain", &Object::release)
        .def_property_readonly("reference_count", &Object::referenceCount);
  }

  static void bindScene(pyb::module& m) {
    pyb::class_<Scene, PyScene, Object, Rc<Scene>>(m, "Scene")
        .def("onUpdate", &Scene::onUpdate)
        .def(pyb::init<>());
  }

  static void bindSceneManager(pyb::module& m) {
    pyb::class_<SceneManager, std::unique_ptr<SceneManager, pyb::nodelete>>(
        m, "SceneManager")
        .def("addScene",
             [](SceneManager* self, PyScene* scene) { self->addScene(scene); })
        .def("setSceneByID", &SceneManager::setSceneByID)
        .def("setSceneLimit", &SceneManager::setSceneLimit)
        .def("getCurrentSceneID", &SceneManager::getCurrentSceneID)
        .def("updateCurrentScene", &SceneManager::updateCurrentScene)
        .def("deleteAllScenes", &SceneManager::deleteAllScenes)
        .def("getCurrentScene", &SceneManager::getCurrentScene);
  }

  static void bindRender3DSystem(pyb::module& m) {
    pyb::class_<Render3DSystem, std::unique_ptr<Render3DSystem, pyb::nodelete>>(
        m, "Render3DSystem")
        .def_static("getInstance", &Render3DSystem::getInstance,
                    pyb::return_value_policy::reference)
        .def("setSkyColor", &Render3DSystem::setSkyColor)
        .def("getSkyColor", &Render3DSystem::getSkyColor)
        .def("getWidth", &Render3DSystem::getWidth)
        .def("getHeight", &Render3DSystem::getHeight);
  }

  static void bindColor(pyb::module& m) {
    pyb::class_<::Color>(m, "Color")
        .def(pyb::init([](int r, int g, int b, int a) -> Color {
          Color c;
          c.r = static_cast<unsigned char>(r);
          c.g = static_cast<unsigned char>(g);
          c.b = static_cast<unsigned char>(b);
          c.a = static_cast<unsigned char>(a);
          return c;
        }))
        .def("__repr__",
             [](const Color& self) -> std::string {
               return fmt::format("{}", self);
             })
        .def_readwrite("r", &Color::r)
        .def_readwrite("g", &Color::g)
        .def_readwrite("b", &Color::b)
        .def_readwrite("a", &Color::a);
  }

  static void bindLogger(pyb::module& m) {
    pyb::class_<PyLog>(m, "log")
        .def_static("debug", &PyLog::debug)
        .def_static("info", &PyLog::info)
        .def_static("warning", &PyLog::warning)
        .def_static("error", &PyLog::error)
        .def_static("critical", &PyLog::critical);
  }
} // namespace rica::py::bindings

void rica::py::bindings::bindAll(pyb::module& m) {
  bindObject(m);
  bindSceneManager(m);
  bindEngine(m);
  bindRender3DSystem(m);
  bindColor(m);
  bindScene(m);
  bindLogger(m);
}
