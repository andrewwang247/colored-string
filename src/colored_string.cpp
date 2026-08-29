/*
Colored strings implementation.

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"

#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include "base_color.h"

using std::format;
using std::nullopt_t;
using std::ostream;
using std::string;
using std::string_view;

colored_string::colored_string(string_view data)
    : m_data(data), m_foreground(nullptr), m_background(nullptr) {}

colored_string::colored_string(string_view data, const color& fg,
                               const color& bg)
    : m_data(data), m_foreground(fg.clone()), m_background(bg.clone()) {}

colored_string::colored_string(string_view data, const color& fg,
                               nullopt_t /*none*/)
    : m_data(data), m_foreground(fg.clone()), m_background(nullptr) {}

colored_string::colored_string(string_view data, nullopt_t /*none*/,
                               const color& bg)
    : m_data(data), m_foreground(nullptr), m_background(bg.clone()) {}

colored_string::colored_string(string_view data, const color* fg,
                               const color* bg)
    : m_data(data),
      m_foreground(fg ? fg->clone() : nullptr),
      m_background(bg ? bg->clone() : nullptr) {}

colored_string::colored_string(const colored_string& other)
    : m_data(other.m_data),
      m_foreground(other.m_foreground ? other.m_foreground->clone() : nullptr),
      m_background(other.m_background ? other.m_background->clone() : nullptr) {
}

colored_string::colored_string(colored_string&& other) noexcept
    : colored_string() {
  std::swap(*this, other);
}

colored_string& colored_string::operator=(colored_string other) {
  std::swap(*this, other);
  return *this;
}

colored_string& colored_string::set_foreground(const color& fore) {
  m_foreground = fore.clone();
  return *this;
}

const color* colored_string::get_foreground() const noexcept {
  return m_foreground.get();
}

void colored_string::reset_foreground() noexcept { m_foreground.reset(); }

colored_string& colored_string::set_background(const color& back) {
  m_background = back.clone();
  return *this;
}

const color* colored_string::get_background() const noexcept {
  return m_background.get();
}

void colored_string::reset_background() noexcept { m_background.reset(); }

string colored_string::show() const {
  const auto fore_str =
      m_foreground ? format("{}{}m", FORE_CODE, +m_foreground->code()) : "";
  const auto back_str =
      m_background ? format("{}{}m", BACK_CODE, +m_background->code()) : "";
  return fore_str + back_str + m_data + CLEAR_CODE;
}

ostream& operator<<(ostream& os, const colored_string& str) {
  return os << str.show();
}
