#pragma once

// Предварительные объявления
struct Component;
class SpriteComponent;
class TransformComponent;
class Camera2DComponent;
class Physic3DComponent;
class Entity;
class Player;
class Terminal;
class Log;
class Collider2DSystem;
class Render2DSystem;
class AudioSystem;

#include <raylib.h>
#include <raymath.h>

#include <rapidjson/document.h>

#include <memory>
#include <string>
#include <vector>

// переменные
#include "Var/Var.hpp"

#include "Logger/Logger.hpp"

// Компоненты ECS
#include "ECS/Components/Audio/Audio.hpp"
#include "ECS/Components/Camera/Camera2D/Camera2D.hpp"
#include "ECS/Components/Camera/Camera3D/Camera3D.hpp"
#include "ECS/Components/Collider/Collider2D/Collider2D.hpp"
#include "ECS/Components/Component.hpp"
#include "ECS/Components/Mesh/Mesh.hpp"
#include "ECS/Components/Physic/Physic3D/Physic3D.hpp"
#include "ECS/Components/Sprite/Sprite.hpp"
#include "ECS/Components/Transform/Transform2D/Transform.hpp"
#include "ECS/Components/Transform/Transform3D/Transform3D.hpp"
// Объекты ECS
#include "ECS/Objects/Entity.hpp"

// системы
#include "ECS/Systems/Audio/Audio.hpp"
#include "ECS/Systems/Collider/Collider2D/Collider2D.hpp"
#include "ECS/Systems/Graphics/Render2D/Render2D.hpp"
#include "ECS/Systems/Graphics/Render3D/Render3D.hpp"

// Мир
#include "Scene/Scene.hpp"

// Физика
#include "Physic/Physic2D/Physic.hpp"
#include "Physic/Physic3D/Physic.hpp"

// Движок
#include "Engine/Engine.hpp"

// Объект
#include "Object/AutoreleasePool.hpp"
#include "Object/Object.hpp"
#include "Object/ObjectVector.hpp"
#include "Object/PoolManager.hpp"
#include "Object/Rc.hpp"

// Ввод
#include "Input/InputDispatcher.hpp"
#include "Input/InputEvent.hpp"
#include "Input/InputListener.hpp"
#include "Input/InputListenerKeyboard.hpp"
#include "Input/InputListenerMouseButton.hpp"
#include "Input/InputListenerMousePosition.hpp"

// Другое
#include "macros.hpp"
