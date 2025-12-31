/*
Pure virtual base color interface.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

/**
 * 8-bit ANSI color type.
 */
using color_t = unsigned char;

class colored_string;

/**
 * Abstract interface for all color types.
 */
class color {
  friend class colored_string;

 protected:
  /**
   * The ANSI code offset from 0.
   */
  const int m_offset;

  color() = delete;

  /**
   * Argument constructor.
   *
   * @param offset The ANSI code offset.
   */
  explicit color(int offset_in);

 public:
  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  virtual color_t code() const = 0;

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
  virtual std::unique_ptr<color> clone() const = 0;
};

/**
 * Abstract class for colors that are canonically described by a single value.
 */
class singular_color : public color {
 protected:
  const color_t m_color;

  singular_color() = delete;

  /**
   * Argument constructor.
   *
   * @param color_in The underlying color.
   * @param offset_in The ANSI code offset.
   */
  singular_color(color_t color_in, int offset_in);

 public:
  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  color_t code() const override;
};

/**
 * Standard palette colors.
 */
enum class palette : color_t {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE
};
/**
 * The number of palette colors.
 */
static constexpr color_t PALETTE_SIZE = 8;
