/*
Colored strings.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#include "colored_string.h"
using std::ostream;
using std::string;

colored_string::colored_string(const colored_string& other)
    : string(other),
      m_foreground(other.m_foreground ? other.m_foreground->clone() : nullptr),
      m_background(other.m_background ? other.m_background->clone() : nullptr) {
}

colored_string::colored_string(colored_string&& other) : colored_string() {
  std::swap(*this, other);
}

colored_string& colored_string::operator=(colored_string other) {
  std::swap(*this, other);
  return *this;
}

colored_string& colored_string::foreground(const color& fore) {
  m_foreground.reset(fore.clone());
  return *this;
}

const colored_string& colored_string::foreground(const color& fore) const {
  m_foreground.reset(fore.clone());
  return *this;
}

const color* colored_string::foreground() const noexcept {
  return m_foreground.get();
}

void colored_string::reset_foreground() const noexcept { m_foreground.reset(); }

colored_string& colored_string::background(const color& back) {
  m_background.reset(back.clone());
  return *this;
}

const colored_string& colored_string::background(const color& back) const {
  m_background.reset(back.clone());
  return *this;
}

const color* colored_string::background() const noexcept {
  return m_background.get();
}

void colored_string::reset_background() const noexcept { m_background.reset(); }

ostream& operator<<(ostream& os, const colored_string& str) {
  if (str.m_foreground) {
    os << "\033[38;5;" << +str.m_foreground->code() << 'm';
  }
  if (str.m_background) {
    os << "\033[48;5;" << +str.m_background->code() << 'm';
  }
  return os << static_cast<string>(str) << "\033[0m";
}
