#include <rica.hpp>

bool Engine::parseInitFile(rapidjson::Document& doc) {
  std::fstream initFile("initEngine.json");
  if (!initFile.is_open()) {
    rica::log::error("Initialization", "Failed to load initEngine.json");
    return false;
  }
  std::string initString((std::istreambuf_iterator<char>(initFile)),
                         std::istreambuf_iterator<char>());
  doc.Parse(initString.c_str());
  if (doc.HasParseError()) {
    rica::log::error("Initialization", "Failed to parse JSON in position {}",
                     doc.GetErrorOffset());
    return false;
  }
  return true;
}

std::optional<RayLibVar> Engine::parseInitFileForRayLib() {
  static auto& render3Dsystem = Render3DSystem::getInstance();
  static auto& render2Dsystem = Render2DSystem::getInstance();

  RayLibVar rayVar;
  rayVar.flag = 0;
  rapidjson::Document doc;

  if (!parseInitFile(doc))
    return {};

  // Ранний выход, если нет корневого объекта "rayLib"
  if (!doc.HasMember("rayLib") || !doc["rayLib"].IsObject())
    return {};

  const rapidjson::Value& config = doc["rayLib"];

  // 1. Парсинг заголовка и FPS
  if (config.HasMember("windowTitle") && config["windowTitle"].IsString())
    rayVar.title = config["windowTitle"].GetString();
  if (config.HasMember("maxFPS") && config["maxFPS"].IsInt())
    rayVar.maxFPS = config["maxFPS"].GetInt();

  // 2. Парсинг разрешения и флагов
  if (config.HasMember("resolution") && config["resolution"].IsObject()) {
    const rapidjson::Value& resolution = config["resolution"];

    auto parseDimension = [&](const char* key, int& dimension) {
      if (!resolution.HasMember(key))
        return;
      const rapidjson::Value& value = resolution[key];
      if (value.IsInt()) {
        dimension = value.GetInt();
      } else if (value.IsString()) {
        std::string strValue = value.GetString();
      }
    };

    parseDimension("width", rayVar.width);
    parseDimension("height", rayVar.height);

    if (config.HasMember("configurationFlags") &&
        config["configurationFlags"].IsArray()) {
      const rapidjson::Value& flagsArray = config["configurationFlags"];
      for (rapidjson::SizeType i = 0; i < flagsArray.Size(); i++) {
        if (flagsArray[i].IsString()) {
          std::string flagString = flagsArray[i].GetString();
          if (auto flag = RayLibVar::getFlagValue(flagString))
            rayVar.flag |= *flag;
          else
            rica::log::error("Engine", "Unknown flag {}", flagString);
        }
      }
    }
  }

  SetConfigFlags(rayVar.flag);
  InitWindow(rayVar.width, rayVar.height, rayVar.title.c_str());
  if (is3Dmode())
    render3Dsystem.init(rayVar.width, rayVar.height);
  else
    render2Dsystem.init(rayVar.width, rayVar.height);

  SetTargetFPS(rayVar.maxFPS);

  return rayVar;
}
