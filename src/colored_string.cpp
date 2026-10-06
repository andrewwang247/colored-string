/*
String with foreground and background colors.

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <print>
#include <string_view>

#include "true_color.h"

using std::format_context;
using std::formatter;
using std::ostream;
using std::print;

using std::string_view_literals::operator""sv;

static constexpr auto FORE_TEMPLATE = "\x1b[38;2;{};{};{}m";
static constexpr auto BACK_TEMPLATE = "\x1b[48;2;{};{};{}m";
static constexpr auto CLEAR_CODE = "\x1b[0m"sv;

namespace cs {

ostream& operator<<(ostream& os, const colored_string& cs) {
  if (cs.foreground) {
    const auto [r, g, b] = *cs.foreground;
    print(os, FORE_TEMPLATE, r, g, b);
  }

  if (cs.background) {
    const auto [r, g, b] = *cs.background;
    print(os, BACK_TEMPLATE, r, g, b);
  }

  // Respect stream formatting on string data only.
  os << cs.data;

  if (cs.foreground || cs.background) {
    print(os, CLEAR_CODE);
  }

  return os;
}

}  // namespace cs

format_context::iterator formatter<cs::colored_string>::format(
    const cs::colored_string& cs, format_context& ctx) const {
  auto out = ctx.out();

  if (cs.foreground) {
    const auto [r, g, b] = *cs.foreground;
    out = std::format_to(out, FORE_TEMPLATE, r, g, b);
  }

  if (cs.background) {
    const auto [r, g, b] = *cs.background;
    out = std::format_to(out, BACK_TEMPLATE, r, g, b);
  }

  // Apply formatting to only the string data.
  out = std::vformat_to(out, fmt_args, std::make_format_args(cs.data));

  if (cs.foreground || cs.background) {
    out = std::ranges::copy(CLEAR_CODE, out).out;
  }

  return out;
}
