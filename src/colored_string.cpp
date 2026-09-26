/*
String with foreground and background colors.

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <string_view>

#include "parse.h"
#include "true_color.h"

using channel::color_t;
using std::array;
using std::format_context;
using std::formatter;
using std::ostream;

using std::string_view_literals::operator""sv;

static constexpr auto FORE_CODE = "\x1b[38;2;"sv;
static constexpr auto BACK_CODE = "\x1b[48;2;"sv;
static constexpr auto CLEAR_CODE = "\x1b[0m"sv;

ostream& operator<<(ostream& os, const colored_string& cs) {
  array<char, parse::DIGITS> buffer{};

  const auto write_num = [&os, &buffer](color_t color, char append) {
    const auto sv = parse::to_str(buffer, color);
    parse::write_sv(os, sv);
    os.put(append);
  };

  if (cs.foreground) {
    parse::write_sv(os, FORE_CODE);
    write_num(cs.foreground->red, ';');
    write_num(cs.foreground->green, ';');
    write_num(cs.foreground->blue, 'm');
  }

  if (cs.background) {
    parse::write_sv(os, BACK_CODE);
    write_num(cs.background->red, ';');
    write_num(cs.background->green, ';');
    write_num(cs.background->blue, 'm');
  }

  // Respect stream state on string data only.
  os << cs.data;

  if (cs.foreground || cs.background) {
    parse::write_sv(os, CLEAR_CODE);
  }

  return os;
}

format_context::iterator formatter<colored_string>::format(
    const colored_string& cs, format_context& ctx) const {
  using std::make_format_args;
  using std::vformat_to;
  using std::ranges::copy;

  auto out = ctx.out();
  array<char, parse::DIGITS> buffer{};

  const auto write_num = [&out, &buffer](color_t color, char append) {
    const auto sv = parse::to_str(buffer, color);
    out = copy(sv, out).out;
    *out++ = append;
  };

  if (cs.foreground) {
    out = copy(FORE_CODE, out).out;
    write_num(cs.foreground->red, ';');
    write_num(cs.foreground->green, ';');
    write_num(cs.foreground->blue, 'm');
  }

  if (cs.background) {
    out = copy(BACK_CODE, out).out;
    write_num(cs.background->red, ';');
    write_num(cs.background->green, ';');
    write_num(cs.background->blue, 'm');
  }

  // Apply formatting to only the string data.
  out = vformat_to(out, fmt_args, make_format_args(cs.data));

  if (cs.foreground || cs.background) {
    out = copy(CLEAR_CODE, out).out;
  }
  return out;
}
