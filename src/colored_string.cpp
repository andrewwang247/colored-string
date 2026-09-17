/*
Colored strings implementation.

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"

#include <iostream>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <utility>

#include "base_color.h"

using std::optional;
using std::ostream;
using std::print;
using std::string;
using std::string_view;

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
  if (str.m_foreground) {
    print(os, "{}{}m", colored_string::FORE_CODE, str.m_foreground.value());
  }
  if (str.m_background) {
    print(os, "{}{}m", colored_string::BACK_CODE, str.m_background.value());
  }
  os << str.m_data;
  if (str.m_foreground || str.m_background) {
    print(os, colored_string::CLEAR_CODE);
  }
  return os;
}
