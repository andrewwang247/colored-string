/*
String representation of color types.

Copyright 2026. Andrew Wang.
*/
#include "parse.h"

#include <array>
#include <charconv>
#include <iostream>
#include <string_view>
#include <system_error>

#include "true_color.h"

using std::array;
using std::make_error_code;
using std::ostream;
using std::streamsize;
using std::string_view;
using std::system_error;
using std::to_chars;

string_view parse::to_str(array<char, DIGITS>& buffer, color_t col) {
  const auto [ptr, ec] = to_chars(buffer.begin(), buffer.end(), col);
  if (ec != std::errc{}) {
    throw system_error(make_error_code(ec), "Could not convert to string");
  }
  return {buffer.begin(), ptr};
}

void parse::write_sv(ostream& os, string_view sv) {
  os.write(sv.data(), static_cast<streamsize>(sv.length()));
}
