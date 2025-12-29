#pragma once
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace rica::py::bindings {
  void bindAll(pybind11::module& m);
} // namespace rica::py::bindings
