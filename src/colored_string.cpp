/*
Colored strings.

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"

#include <format>
#include <iostream>
#include <string>
#include <utility>

using std::format;
using std::ostream;
using std::string;

colored_string::colored_string(const colored_string& other)
    : string(other),
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

colored_string& colored_string::foreground(const color& fore) {
  m_foreground = fore.clone();
  return *this;
}

const colored_string& colored_string::foreground(const color& fore) const {
  m_foreground = fore.clone();
  return *this;
}

const color* colored_string::foreground() const noexcept {
  return m_foreground.get();
}

void colored_string::reset_foreground() const noexcept { m_foreground.reset(); }

colored_string& colored_string::background(const color& back) {
  m_background = back.clone();
  return *this;
}

const colored_string& colored_string::background(const color& back) const {
  m_background = back.clone();
  return *this;
}

const color* colored_string::background() const noexcept {
  return m_background.get();
}

void colored_string::reset_background() const noexcept { m_background.reset(); }

string colored_string::show() const {
  const auto fore_str =
      m_foreground ? format("{}{}m", FORE_CODE, +m_foreground->code()) : "";
  const auto back_str =
      m_background ? format("{}{}m", BACK_CODE, +m_background->code()) : "";
  return format(
      "{}{}{}{}", fore_str, back_str,
      static_cast<string>(*this),  // NOLINT(cppcoreguidelines-slicing)
      colored_string::CLEAR_CODE);
}

ostream& operator<<(ostream& os, const colored_string& str) {
  return os << str.show();
}
