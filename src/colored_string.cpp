/*
Colored strings implementation.

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"

#include <array>
#include <charconv>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include "base_color.h"

using std::array;
using std::errc;
using std::make_error_code;
using std::optional;
using std::ostream;
using std::streamsize;
using std::string;
using std::string_view;
using std::system_error;
using std::to_chars;

colored_string::colored_string(string data, optional<color_t> fg,
                               optional<color_t> bg) noexcept
    : m_data(std::move(data)), m_foreground(fg), m_background(bg) {}

colored_string::builder& colored_string::builder::data(
    string_view sv) noexcept {
  m_str = sv;
  return *this;
}

colored_string::builder& colored_string::builder::foreground(
    const color& fg) noexcept {
  m_fore = fg.code();
  return *this;
}

colored_string::builder& colored_string::builder::background(
    const color& bg) noexcept {
  m_back = bg.code();
  return *this;
}

colored_string colored_string::builder::build() noexcept {
  return {std::move(m_str), m_fore, m_back};
}

colored_string& colored_string::set_foreground(const color& fore) {
  m_foreground = fore.code();
  return *this;
}

void colored_string::reset_foreground() noexcept { m_foreground.reset(); }

colored_string& colored_string::set_background(const color& back) {
  m_background = back.code();
  return *this;
}

void colored_string::reset_background() noexcept { m_background.reset(); }

ostream& operator<<(ostream& os, const colored_string& str) {
  const auto write_code = [&os](string_view escape, color_t code) {
    array<char, 3> buffer{};  // max of 3 base-10 digits for a code
    os.write(escape.data(), static_cast<streamsize>(escape.length()));
    const auto [ptr, ec] = to_chars(buffer.begin(), buffer.end(), code);
    if (ec != errc{}) {
      throw system_error(make_error_code(ec),
                         "Could not convert code to chars");
    }
    os.write(buffer.data(), ptr - buffer.begin());
    os.put('m');
  };

  if (str.m_foreground)
    write_code(colored_string::FORE_CODE, *str.m_foreground);
  if (str.m_background)
    write_code(colored_string::BACK_CODE, *str.m_background);

  // Use operator<< to respect formatting
  os << str.m_data;

  if (str.m_foreground || str.m_background) {
    os.write(colored_string::CLEAR_CODE.data(),
             static_cast<streamsize>(colored_string::CLEAR_CODE.length()));
  }

  return os;
}
