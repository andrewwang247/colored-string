/*
String with foreground and background colors.

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"

#include <algorithm>
#include <array>
#include <format>
#include <iostream>

#include "parse.h"
#include "true_color.h"

using std::array;
using std::format_context;
using std::formatter;
using std::ostream;
using std::streamsize;

ostream& operator<<(ostream& os, const colored_string& cs) {
  array<char, parse::DIGITS> buffer{};

  const auto write_num = [&os, &buffer](color_t color, char append) {
    const auto sv = parse::to_str(buffer, color);
    parse::write_sv(os, sv);
    os.put(append);
  };

  if (cs.foreground) {
    parse::write_sv(os, parse::FORE_CODE);
    write_num(cs.foreground->red, ';');
    write_num(cs.foreground->green, ';');
    write_num(cs.foreground->blue, 'm');
  }

  if (cs.background) {
    parse::write_sv(os, parse::BACK_CODE);
    write_num(cs.background->red, ';');
    write_num(cs.background->green, ';');
    write_num(cs.background->blue, 'm');
  }

  // Respect stream state on string data only.
  os << cs.data;

  if (cs.foreground || cs.background) {
    parse::write_sv(os, parse::CLEAR_CODE);
  }

  return os;
}

format_context::iterator formatter<colored_string>::format(
    const colored_string& cs, format_context& ctx) const {
  auto out = ctx.out();
  array<char, parse::DIGITS> buffer{};

  const auto write_num = [&out, &buffer](color_t color, char append) {
    const auto sv = parse::to_str(buffer, color);
    out = std::ranges::copy(sv, out).out;
    *out++ = append;
  };

  if (cs.foreground) {
    out = std::ranges::copy(parse::FORE_CODE, out).out;
    write_num(cs.foreground->red, ';');
    write_num(cs.foreground->green, ';');
    write_num(cs.foreground->blue, 'm');
  }

  if (cs.background) {
    out = std::ranges::copy(parse::BACK_CODE, out).out;
    write_num(cs.background->red, ';');
    write_num(cs.background->green, ';');
    write_num(cs.background->blue, 'm');
  }

  // Apply formatting to only the data.
  out = std::vformat_to(out, fmt_args, std::make_format_args(cs.data));

  if (cs.foreground || cs.background) {
    out = std::ranges::copy(parse::CLEAR_CODE, out).out;
  }
  return out;
}
