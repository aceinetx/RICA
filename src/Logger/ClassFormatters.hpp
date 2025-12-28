#pragma once
#include <fmt/base.h>
#include <raylib.h>

namespace fmt {
  template <> class formatter<Color> {
  public:
    constexpr auto parse(format_parse_context& ctx) {
      return ctx.begin();
    }
    template <typename Context>
    constexpr auto format(Color const& obj, Context& ctx) const {
      return format_to(ctx.out(), "Color({},{},{},{})", obj.r, obj.g, obj.b,
                       obj.a);
    }
  };

  template <> class formatter<Vector2> {
  public:
    constexpr auto parse(format_parse_context& ctx) {
      return ctx.begin();
    }
    template <typename Context>
    constexpr auto format(Vector2 const& obj, Context& ctx) const {
      return format_to(ctx.out(), "Vector2({},{})", obj.x, obj.y);
    }
  };
} // namespace fmt
