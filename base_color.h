/*
Pure virtual base color interface.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#pragma once
#include "color.h"

class colored_string;

/**
 * Abstract interface for all color types.
 */
class color {
  friend class colored_string;

 public:
  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  virtual color_t code() const noexcept = 0;

  /**
   * Default virtual destructor.
   */
  virtual ~color() noexcept = default;

 private:
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  virtual color* clone() const = 0;
};
