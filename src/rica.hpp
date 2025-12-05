#pragma once

// Предварительные объявления
struct Component;
class SpriteComponent;
class TransformComponent;
class Camera2DComponent;
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
#include "ECS/Components/Lightning/Lightning3D.hpp"
#include "ECS/Components/Mesh/Mesh.hpp"
#include "ECS/Components/Sprite/Sprite.hpp"
#include "ECS/Components/Transform/Transform2D/Transform.hpp"
#include "ECS/Components/Transform/Transform3D/Transform3D.hpp"

// Объекты ECS
#include "ECS/Objects/Entity.hpp"

// системы
#include "Audio/Audio.hpp"
#include "Collider/Collider2D/Collider2D.hpp"
#include "graphics/Render2D/Render2D.hpp"
#include "graphics/Render3D/Render3D.hpp"

// Мир
#include "Scene/Scene.hpp"

// Движок
#include "engine/Engine.hpp"