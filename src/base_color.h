/*
Abstract base colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

/**
 * @brief 8-bit ANSI color type.
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
constexpr color_t color_cast(color_specifier auto cs) noexcept {
  return static_cast<color_t>(cs);
}

/**
 * @brief Abstract interface for all color types.
 */
class color {
 protected:
  // The ANSI code offset from 0.
  color_t m_offset;

  /**
   * @brief Argument constructor.
   * @param offset The ANSI code offset.
   */
  explicit color(color_t offset) noexcept;

  color(const color&) noexcept;
  color& operator=(const color& other) noexcept;

 public:
  /**
   * @brief See below.
   * @return The 8-bit ANSI color code.
   */
  virtual color_t code() const noexcept = 0;

  /**
   * @brief Polymorphic cloning.
   * @return A new copy of the color.
   */
  virtual std::unique_ptr<color> clone() const = 0;

  virtual ~color() noexcept;
};
