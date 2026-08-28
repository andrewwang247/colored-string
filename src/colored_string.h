/*
Colored strings.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include "base_color.h"

/**
 * String that maintains foreground and background colors.
 */
class colored_string {
 private:
  // ANSI 8-bit escape sequences
  static constexpr auto FORE_CODE = "\x1b[38;5;";
  static constexpr auto BACK_CODE = "\x1b[48;5;";
  static constexpr auto CLEAR_CODE = "\x1b[0m";

  std::string m_data;
  std::unique_ptr<color> m_foreground, m_background;

 public:
  explicit colored_string() = default;

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
   * @brief Constructor with pointers to colors.
   * @param data String value for this.
   * @param fg Pointer to foreground color.
   * @param bg Pointer to background color.
   */
  colored_string(std::string_view data, const color* fg, const color* bg);

  /**
   * @brief Copy constructor.
   * @param other The other string.
   */
  colored_string(const colored_string& other);

  /**
   * @brief Move constructor.
   * @param other The other string.
   */
  colored_string(colored_string&& other) noexcept;

  /**
   * @brief Assignment operator for copy and move.
   * @param other The other string.
   * @return A reference to this.
   */
  colored_string& operator=(colored_string other);

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
   * @brief Get foreground color. Null if not present.
   * @return Pointer to foreground color.
   */
  const color* get_foreground() const noexcept;

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
   * @brief Get background color. Null if not present.
   * @return Pointer to background color.
   */
  const color* get_background() const noexcept;

  /**
   * @brief Reset background color to default.
   */
  void reset_background() noexcept;

  /**
   * @brief Get the string that is printed to get colors.
   * @returns The constructed string with included ANSI color codes.
   */
  std::string show() const;

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
