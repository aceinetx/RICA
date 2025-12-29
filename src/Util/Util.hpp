#pragma once
#include <string>
#include <tl/expected.hpp>

namespace rica::util {
  tl::expected<std::string, std::string> readFile(const std::string& filename);
}
