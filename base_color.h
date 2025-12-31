/*
Pure virtual base color interface.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>
#include <type_traits>

/**
 * 8-bit ANSI color type.
 */
using color_t = unsigned char;

/**
 * Cast to the underlying color type.
 * @param ce The color enum class.
 * @return Cast to the underlying color_t.
 */
template <typename T>
constexpr color_t color_cast(T ce);

/**
 * Cast to the enum type.
 * @param col The underlying color.
 * @return An enum with this value.
 */
template <typename T>
constexpr T enum_cast(color_t col);

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
  color_t m_offset;

  color() = default;

  /**
   * Argument constructor.
   *
   * @param offset The ANSI code offset.
   */
  explicit color(color_t offset_in);

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
  color_t m_color;

  singular_color() = default;

  /**
   * Argument constructor.
   *
   * @param color_in The underlying color.
   * @param offset_in The ANSI code offset.
   */
  singular_color(color_t color_in, color_t offset_in);

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
  WHITE,

  END
};

// TEMPLATED IMPLEMENTATIONS

template <typename T>
constexpr color_t color_cast(T ce) {
  static_assert(std::is_same_v<std::underlying_type_t<T>, color_t>,
                "Input must be an enum with underlying type color_t");
  return static_cast<color_t>(ce);
}

template <typename T>
constexpr T enum_cast(color_t col) {
  static_assert(std::is_same_v<std::underlying_type_t<T>, color_t>,
                "Input must be an enum with underlying type color_t");
  return static_cast<T>(col);
}
