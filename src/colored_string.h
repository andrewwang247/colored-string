/*
String with foreground and background colors.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <compare>
#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

#include "true_color.h"

/**
 * @brief String with foreground and background colors.
 */
class colored_string {
  friend struct std::formatter<colored_string>;

 public:
  std::string data;
  std::optional<true_color> foreground, background;

  auto operator<=>(const colored_string&) const = default;

  /**
   * @brief Stream insertion with colors.
   * @param os The output stream.
   * @param cs Colored string to print.
   * @return Reference to output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const colored_string& cs);
};

template <>
struct std::formatter<colored_string> : std::formatter<std::string_view> {
  std::string fmt_args;

  /**
   * @brief Capture full option specifier until closing brace.
   * @param ctx The parsing context.
   * @return Iterator to end of specifier.
   */
  [[maybe_unused]] constexpr auto parse(std::format_parse_context& ctx);

  /**
   * @brief Format colored_string properly.
   * @param cs The colored_string to format.
   * @param ctx The formatting context.
   * @returns The format context.
   */
  [[maybe_unused]] std::format_context::iterator format(
      const colored_string& cs, std::format_context& ctx) const;
};

// CONSTEXPR IMPLEMENTATIONS

constexpr auto std::formatter<colored_string>::parse(
    std::format_parse_context& ctx) {
  const auto* it = std::ranges::find(ctx, '}');
  const auto ctx_args = std::string_view{ctx.begin(), it};
  fmt_args.reserve(ctx_args.length() + 3);
  fmt_args += "{:";
  fmt_args += ctx_args;
  fmt_args += '}';
  return it;
}
