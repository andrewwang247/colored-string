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
  static constexpr auto FORE_CODE = "\x1b[38;5;";
  static constexpr auto BACK_CODE = "\x1b[48;5;";
  static constexpr auto CLEAR_CODE = "\x1b[0m";

  std::string m_data;
  std::optional<color_t> m_foreground, m_background;

 public:
  /**
   * @brief Data only constructor.
   * @param data String value for this.
   */
  explicit colored_string(std::string_view data);

  /**
   * @brief Constructor with colors.
   * @param data String value for this.
   * @param fg Reference to foreground color.
   * @param bg Reference to background color.
   */
  colored_string(std::string_view data, const color& fg, const color& bg);

  /**
   * @brief Constructor with only foreground.
   * @param data String value for this.
   * @param fg Reference to foreground color.
   * @param none No color for background.
   */
  colored_string(std::string_view data, const color& fg, std::nullopt_t none);

  /**
   * @brief Constructor with only background.
   * @param data String value for this.
   * @param none No color for foreground.
   * @param bg Reference to background color.
   */
  colored_string(std::string_view data, std::nullopt_t none, const color& bg);

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
