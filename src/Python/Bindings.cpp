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

  static void bindEngine(pyb::module& m) {
    pyb::class_<Engine, std::unique_ptr<Engine, pyb::nodelete>>(m, "Engine")
        .def_static("getInstance", &Engine::getInstance,
                    pyb::return_value_policy::reference)
        .def("set3Dmode", &Engine::set3Dmode)
        .def("init", &Engine::init)
        .def("mainLoop", &Engine::mainLoop)
        .def_readwrite("sceneManager", &Engine::sceneManager);
  }

  static void bindObject(pyb::module& m) {
    pyb::class_<Object, Rc<Object>>(m, "Object")
        .def(pyb::init<>())
        .def("autorelease",
             [](Rc<Object> self) { PoolManager::getInstance().add(self); })
        .def("release", &Object::retain)
        .def("retain", &Object::release);
  }

  static void bindScene(pyb::module& m) {
#if 0
    pyb::class_<Scene, Object, Rc<Scene>>(m, "Scene")
        .def("onUpdate", &Scene::onUpdate)
        .def(pyb::init<>());
#else
    pyb::class_<Scene, PyScene, Object, Rc<Scene>>(m, "Scene")
        .def("onUpdate", &Scene::onUpdate)
        .def(pyb::init<>());
#endif
  }

  static void bindSceneManager(pyb::module& m) {
    pyb::class_<SceneManager, std::unique_ptr<SceneManager, pyb::nodelete>>(
        m, "SceneManager")
        .def("addScene",
             [](SceneManager* self, PyScene* scene) { self->addScene(scene); });
  }

  static void bindRender3DSystem(pyb::module& m) {
    pyb::class_<Render3DSystem, std::unique_ptr<Render3DSystem, pyb::nodelete>>(
        m, "Render3DSystem")
        .def_static("getInstance", &Render3DSystem::getInstance,
                    pyb::return_value_policy::reference)
        .def("setSkyColor", &Render3DSystem::setSkyColor);
  }

  static void bindColor(pyb::module& m) {
    pyb::class_<::Color>(m, "Color")
        .def("__init__", [](Color& self, int r, int g, int b, int a) {
          self.r = static_cast<unsigned char>(r);
          self.g = static_cast<unsigned char>(g);
          self.b = static_cast<unsigned char>(b);
          self.a = static_cast<unsigned char>(a);
        });
    ;
  }
} // namespace rica::py::bindings

void rica::py::bindings::bindAll(pyb::module& m) {
  bindObject(m);
  bindSceneManager(m);
  bindEngine(m);
  bindRender3DSystem(m);
  bindColor(m);
  bindScene(m);
}
