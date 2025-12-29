#include "Util/Util.hpp"
#include <fmt/format.h>
#include <fstream>
#include <sstream>

tl::expected<std::string, std::string>
rica::util::readFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    return tl::unexpected(fmt::format("could not open {}", filename));
    exit(1);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return {buffer.str()};
}
