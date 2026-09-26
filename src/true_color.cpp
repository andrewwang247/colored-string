/*
ANSI 24 bit true color.

Copyright 2026. Andrew Wang.
*/
#include "true_color.h"

#include <format>
#include <stdexcept>
#include <string>
#include <string_view>

#include "parse.h"

using channel::color_t;
using std::format;
using std::invalid_argument;
using std::string;
using std::string_view;

true_color true_color::from_hex(string_view hex_code) {
  if (hex_code.empty()) {
    throw invalid_argument("Hex code cannot be empty");
  }
  if (hex_code.front() == '#') {
    hex_code.remove_prefix(1);
  }
  if (hex_code.length() != 6) {
    throw invalid_argument(
        "Hex code must have length 6 after removing optional #");
  }

  static constexpr auto HEX_BASE = 16;
  const auto red = parse::from_str<color_t, HEX_BASE>(hex_code.substr(0, 2));
  const auto green = parse::from_str<color_t, HEX_BASE>(hex_code.substr(2, 2));
  const auto blue = parse::from_str<color_t, HEX_BASE>(hex_code.substr(4, 2));

  return {.red = red, .green = green, .blue = blue};
}

std::string true_color::hex() const {
  return format("#{:02X}{:02X}{:02X}", red, green, blue);
}

true_color true_color::operator~() const noexcept {
  return {.red = static_cast<color_t>(~red),
          .green = static_cast<color_t>(~green),
          .blue = static_cast<color_t>(~blue)};
}
