/*
String representation of color types.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <charconv>
#include <concepts>
#include <stdexcept>
#include <string_view>
#include <system_error>

#include "true_color.h"

namespace cs::parse {

template <typename T>
concept numeric = std::integral<T> || std::floating_point<T>;

template <numeric T, int Base = 10>
T from_str(std::string_view sv) {
  static_assert(Base > 0);
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
    throw std::system_error(std::make_error_code(ec),
                            "Failed to convert from string");
  }
  if (ptr != sv.end()) {
    throw std::invalid_argument("Failed to convert entire string");
  }
  return result;
}

}  // namespace cs::parse
