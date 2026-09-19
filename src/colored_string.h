/*
Colored strings interface.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include "base_color.h"
#include "util.h"

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
                 std::optional<color_t> bg);

  friend struct std::formatter<colored_string>;

 public:
  /**
   * @brief Default constructor with no data or color.
   */
  explicit colored_string() = default;

  /**
   * @brief Construct with only string data and no colors.
   * @param data The raw string data.
   */
  explicit colored_string(std::string_view data);

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

/**
 * @brief Custom formatter for colored_string.
 */
template <>
struct std::formatter<colored_string> : std::formatter<std::string_view> {
  std::string fmt_args;

  /**
   * @brief Capture full option specifier until closing brace.
   * @param ctx The parsing context.
   * @return Iterator to end of specifier.
   */
  [[maybe_unused]] constexpr auto parse(std::format_parse_context& ctx) {
    const auto* it = std::ranges::find(ctx, '}');
    const auto ctx_args = std::string_view{ctx.begin(), it};
    fmt_args.reserve(ctx_args.length() + 3);
    fmt_args += "{:";
    fmt_args += ctx_args;
    fmt_args += '}';
    return it;
  }

  /**
   * @brief Format colored_string properly.
   * @param str The colored_string to format.
   * @param ctx The formatting context.
   * @returns The format context.
   */
  [[maybe_unused]] auto format(const colored_string& str,
                               std::format_context& ctx) const {
    auto out = ctx.out();

    const auto write_code = [&out](string_view escape, color_t code) {
      util::col_str_buffer buffer;
      const auto sv = util::color_to_str(buffer, code);

      out = std::ranges::copy(escape, out).out;
      out = std::ranges::copy(sv, out).out;
      *out++ = 'm';
    };

    if (str.m_foreground)
      write_code(colored_string::FORE_CODE, *str.m_foreground);
    if (str.m_background)
      write_code(colored_string::BACK_CODE, *str.m_background);

    // Apply formatting to only the data.
    out = std::vformat_to(out, fmt_args, std::make_format_args(str.m_data));

    if (str.m_foreground || str.m_background) {
      out = std::ranges::copy(colored_string::CLEAR_CODE, out).out;
    }
    return out;
  }
};
