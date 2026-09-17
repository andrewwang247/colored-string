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

#include "base_color.h"

using std::nullopt_t;
using std::ostream;
using std::print;
using std::string;
using std::string_view;

colored_string::colored_string(string_view data) : m_data(data) {}

colored_string::colored_string(string_view data, const color& fg,
                               const color& bg)
    : m_data(data), m_foreground(fg.code()), m_background(bg.code()) {}

colored_string::colored_string(string_view data, const color& fg,
                               nullopt_t /*none*/)
    : m_data(data), m_foreground(fg.code()) {}

colored_string::colored_string(string_view data, nullopt_t /*none*/,
                               const color& bg)
    : m_data(data), m_background(bg.code()) {}

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
    print(os, "{}{}m", colored_string::FORE_CODE, +str.m_foreground.value());
  }
  if (str.m_background) {
    print(os, "{}{}m", colored_string::BACK_CODE, +str.m_background.value());
  }
  os << str.m_data;
  if (str.m_foreground || str.m_background) {
    print(os, colored_string::CLEAR_CODE);
  }
  return os;
}
