/*
Colored strings interface.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include "base_color.h"

/**
 * @brief String that maintains foreground and background colors.
 */
class colored_string {
 private:
  // ANSI 8-bit escape sequences
  static constexpr std::string_view FORE_CODE = "\x1b[38;5;";
  static constexpr std::string_view BACK_CODE = "\x1b[48;5;";
  static constexpr std::string_view CLEAR_CODE = "\x1b[0m";

  std::string m_data;
  std::optional<color_t> m_foreground, m_background;

  /**
   * @brief Private constructor for use with builder.
   * @param data The raw string data.
   * @param fg The foreground color code.
   * @param bg The background color code.
   */
  colored_string(std::string data, std::optional<color_t> fg,
                 std::optional<color_t> bg) noexcept;

 public:
  /**
   * @brief Fluent builder for colored_string.
   * @warning Cannot re-build the same instance. Data is moved!
   */
  class builder {
   private:
    std::string m_str;
    std::optional<color_t> m_fore, m_back;

   public:
    builder& data(std::string_view sv) noexcept;
    builder& foreground(const color& fg) noexcept;
    builder& background(const color& bg) noexcept;
    colored_string build() noexcept;
  };

  /**
   * @brief Expose underlying string. Modifiable if non-const.
   * @param self Explicit object parameter.
   * @return Reference to the string data.
   */
  template <typename Self>
  auto&& data_reference(this Self&& self);

  /**
   * @brief Modify the foreground color.
   * @param fore The color of the foreground.
   * @return A reference to this.
   */
  colored_string& set_foreground(const color& fore);

  /**
   * @brief Reset foreground color to default.
   */
  void reset_foreground() noexcept;

  /**
   * @brief Modify the background color.
   * @param back The color of the background.
   * @return A reference to this.
   */
  colored_string& set_background(const color& back);

  /**
   * @brief Reset background color to default.
   */
  void reset_background() noexcept;

  /**
   * @brief Spaceship operator for lexicographic comparison.
   * @param other The colored string to compare against.
   * @return Ordering relation between this and other.
   */
  auto operator<=>(const colored_string& other) const noexcept = default;

  /**
   * @brief Print with foreground and background colors.
   * @param os The output stream.
   * @param str Colored string to print.
   * @return Reference to output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const colored_string& str);
};

// TEMPLATED IMPLEMENTATIONS

template <typename Self>
auto&& colored_string::data_reference(this Self&& self) {
  return std::forward<Self>(self).m_data;
}
