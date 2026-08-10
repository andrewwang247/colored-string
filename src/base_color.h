/*
Pure virtual base color interface.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

/**
 * 8-bit ANSI color type.
 */
using color_t = unsigned char;

template <typename T>
concept color_specifier = std::same_as<std::underlying_type_t<T>, color_t> ||
                          std::same_as<T, color_t>;

/**
 * @brief Cast to the underlying color type.
 * @param cs The color specifier class.
 * @return Cast to the underlying color_t.
 */
constexpr color_t color_cast(color_specifier auto cs) {
  return static_cast<color_t>(cs);
}

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

  /**
   * @brief Argument constructor.
   * @param offset The ANSI code offset.
   */
  explicit color(color_t offset_in);

 public:
  /**
   * @brief See below.
   * @return The 8-bit ANSI color code.
   */
  virtual color_t code() const = 0;

  virtual ~color() noexcept = default;

 private:
  /**
   * @brief Polymorphic cloning.
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

  /**
   * @brief Argument constructor.
   * @param color_in The underlying color.
   * @param offset_in The ANSI code offset.
   */
  singular_color(color_t color_in, color_t offset_in);

 public:
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
