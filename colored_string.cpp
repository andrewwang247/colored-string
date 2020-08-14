/*
Colored strings.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#include "colored_string.h"
using std::move;
using std::ostream;
using std::string;
using std::swap;

const colored_string& colored_string::foreground(const color& fore) const {
  m_foreground.reset(fore.clone());
  return *this;
}

const color& colored_string::foreground() const { return *m_foreground.get(); }

void colored_string::reset_foreground() const { m_foreground.reset(); }

const colored_string& colored_string::background(const color& back) const {
  m_background.reset(back.clone());
  return *this;
}

const color& colored_string::background() const { return *m_background.get(); }

void colored_string::reset_background() const { m_background.reset(); }

ostream& operator<<(ostream& os, const colored_string& str) {
  if (str.m_foreground) {
    os << "\033[38;5;" << +str.m_foreground->code() << 'm';
  }
  if (str.m_background) {
    os << "\033[48;5;" << +str.m_background->code() << 'm';
  }
  return os << str.c_str() << "\033[0m";
}
