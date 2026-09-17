/*
Abstract base colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <compare>
#include <concepts>
#include <type_traits>

/**
 * @brief 8-bit ANSI color type.
 */
using color_t = unsigned char;

template <typename T>
concept color_specifier =
    std::same_as<T, color_t> ||
    (std::is_enum_v<T> && std::same_as<std::underlying_type_t<T>, color_t>);

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

  color(const color&) noexcept = default;

  color& operator=(const color& other) noexcept = default;

 public:
  /**
   * @brief Get the unique code associated with this color.
   * @return The 8-bit ANSI color code.
   */
  virtual color_t code() const noexcept = 0;

  virtual ~color() noexcept = default;

  /**
   * @brief Equality check based on code.
   * @param lhs The left color to compare.
   * @param rhs The right color to compare.
   * @return Whether lhs and rhs are equal.
   */
  friend bool operator==(const color& lhs, const color& rhs) noexcept;

  /**
   * @brief Spaceship comparison based on code.
   * @param lhs The left color to compare.
   * @param rhs The right color to compare.
   * @return Ordering relation between lhs and rhs.
   */
  inline friend auto operator<=>(const color& lhs, const color& rhs) noexcept;
};

// AUTO RETURN IMPLEMENTATIONS

auto operator<=>(const color& lhs, const color& rhs) noexcept {
  return lhs.code() <=> rhs.code();
}
