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

using std::array;
using std::format_context;
using std::formatter;
using std::ostream;
using std::streamsize;
using std::string_view;

using std::string_view_literals::operator""sv;

static constexpr auto FORE_CODE = "\x1b[38;2;"sv;
static constexpr auto BACK_CODE = "\x1b[48;2;"sv;
static constexpr auto CLEAR_CODE = "\x1b[0m"sv;

namespace cs {

/**
 * @brief Write a string view to an output stream.
 * @param os The output stream to write to.
 * @param sv The string to write.
 */
static void write_sv(ostream& os, string_view sv) {
  os.write(sv.data(), static_cast<streamsize>(sv.length()));
}

ostream& operator<<(ostream& os, const colored_string& cs) {
  const auto write_num = [&os](color_t color, char append) {
    array<char, cs::parse::DIGITS> buffer{};
    const auto sv = parse::to_str(buffer, color);
    write_sv(os, sv);
    os.put(append);
  };

  if (cs.foreground) {
    write_sv(os, FORE_CODE);
    write_num(cs.foreground->red, ';');
    write_num(cs.foreground->green, ';');
    write_num(cs.foreground->blue, 'm');
  }

  if (cs.background) {
    write_sv(os, BACK_CODE);
    write_num(cs.background->red, ';');
    write_num(cs.background->green, ';');
    write_num(cs.background->blue, 'm');
  }

  // Respect stream formatting on string data only.
  os << cs.data;

  if (cs.foreground || cs.background) {
    write_sv(os, CLEAR_CODE);
  }

  return os;
}

}  // namespace cs

format_context::iterator formatter<cs::colored_string>::format(
    const cs::colored_string& cs, format_context& ctx) const {
  auto out = ctx.out();

  const auto write_num = [&out](cs::color_t color, char append) {
    array<char, cs::parse::DIGITS> buffer{};
    const auto sv = cs::parse::to_str(buffer, color);
    out = std::ranges::copy(sv, out).out;
    *out++ = append;
  };

  if (cs.foreground) {
    out = std::ranges::copy(FORE_CODE, out).out;
    write_num(cs.foreground->red, ';');
    write_num(cs.foreground->green, ';');
    write_num(cs.foreground->blue, 'm');
  }

  if (cs.background) {
    out = std::ranges::copy(BACK_CODE, out).out;
    write_num(cs.background->red, ';');
    write_num(cs.background->green, ';');
    write_num(cs.background->blue, 'm');
  }

  // Apply formatting to only the string data.
  out = std::vformat_to(out, fmt_args, std::make_format_args(cs.data));

  if (cs.foreground || cs.background) {
    out = std::ranges::copy(CLEAR_CODE, out).out;
  }

  return out;
}
