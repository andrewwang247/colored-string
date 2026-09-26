/*
Unit tests for colors and cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <cassert>
#include <charconv>
#include <concepts>
#include <fstream>
#include <iterator>
#include <print>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "cylindrical.h"
#include "hsl_color.h"
#include "hsv_color.h"
#include "true_color.h"

namespace unit_test {
static constexpr auto NUM_CASES = 5'000U;
static constexpr auto ANNOUNCE_TEMPLATE = "Test {:>12} -- {:<8} passed";

/**
 * @brief Verify that types match compile time traits.
 */
void color_concepts();

/**
 * @brief Test conversions between true_color and cylindrical types.
 * @param true_colors The sRGB colors.
 * @param hsv_colors The HSV colors.
 * @param hsl_colors The HSL colors.
 */
void rgb_hsvl(std::span<const true_color> true_colors,
              std::span<const hsv_color> hsv_colors,
              std::span<const hsl_color> hsl_colors);

template <typename T>
concept numeric = std::unsigned_integral<T> || std::floating_point<T>;

template <typename T>
concept color_class =
    std::same_as<T, true_color> ||      // NOLINT(whitespace/indent_namespace)
    std::derived_from<T, cylindrical>;  // NOLINT(whitespace/indent_namespace)

/**
 * @brief Read from a 3 column CSV file of uniform type.
 * @tparam CLS The value type of the rows.
 * @tparam T The value type of the entries.
 * @param name The path to the file.
 * @returns Vector of CSV rows as template type.
 */
template <color_class CLS, numeric T>
std::vector<CLS> read_csv(const char* name);
}  // namespace unit_test

// TEMPLATED IMPLEMENTATIONS

template <unit_test::color_class CLS, unit_test::numeric T>
std::vector<CLS> unit_test::read_csv(const char* name) {
  std::ifstream fin{name};
  assert(fin);

  // Skip header line
  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<CLS> data;
  data.reserve(NUM_CASES);

  const auto from_str = [](std::string_view sv) {
    T result{};
    const auto [ptr, ec] = std::from_chars(sv.begin(), sv.end(), result);
    if (ec != std::errc{}) {
      throw std::system_error(std::make_error_code(ec),
                              "Failed to convert numeric");
    }
    if (ptr != sv.end()) {
      throw std::invalid_argument("Failed to convert numeric");
    }
    return result;
  };

  for (std::string line; std::getline(fin, line);) {
    auto row = std::views::split(line, ',') |
               std::views::transform([&from_str](auto&& rng) {
                 return from_str(std::string_view{rng.begin(), rng.end()});
               });

    assert(std::ranges::distance(row) == 3);

    auto it = row.begin();
    const auto col_0 = *it++;
    const auto col_1 = *it++;
    const auto col_2 = *it;

    data.emplace_back(col_0, col_1, col_2);
  }

  assert(data.size() == NUM_CASES);
  std::println("Imported {} rows from {}", NUM_CASES, name);
  return data;
}
