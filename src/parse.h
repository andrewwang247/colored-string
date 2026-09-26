/*
String representation of color types.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <array>
#include <charconv>
#include <concepts>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string_view>
#include <system_error>

#include "true_color.h"

namespace parse {
/**
 * @brief Number of digits required to represent color_t as base 10 string.
 */
static constexpr auto DIGITS = std::numeric_limits<color_t>::digits10 + 1;

/**
 * @brief Convert a color to its base 10 string representation.
 * @param buffer The array to write characters to.
 * @param col The color to convert into its string representation.
 * @return A string_view backed by buffer of the produced string.
 */
std::string_view to_str(std::array<char, DIGITS>& buffer, color_t col);

template <typename T>
concept numeric = std::unsigned_integral<T> || std::floating_point<T>;

template <numeric T, int Base>
T from_str(std::string_view sv);

/**
 * @brief Write a string view to an output stream.
 * @param os The output stream to write to.
 * @param sv The string to write.
 */
void write_sv(std::ostream& os, std::string_view sv);
}  // namespace parse

// TEMPLATED IMPLEMENTATIONS

template <parse::numeric T, int Base>
T parse::from_str(std::string_view sv) {
  static_assert(Base > 0);
  static constexpr auto ERR_MSG = "Failed to convert from string";
  T result{};

  const auto typed_parse = [&result](auto begin, auto end) {
    if constexpr (std::floating_point<T>) {
      return std::from_chars(begin, end, result);
    } else {
      return std::from_chars(begin, end, result, Base);
    }
  };
  const auto [ptr, ec] = typed_parse(sv.begin(), sv.end());

  if (ec != std::errc{}) {
    throw std::system_error(std::make_error_code(ec), ERR_MSG);
  }
  if (ptr != sv.end()) {
    throw std::invalid_argument(ERR_MSG);
  }
  return result;
}
