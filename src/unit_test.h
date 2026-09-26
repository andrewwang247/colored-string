/*
Unit tests for colors and cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <fstream>
#include <iterator>
#include <print>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "cylindrical.h"
#include "hsl_color.h"
#include "hsv_color.h"
#include "true_color.h"

namespace unit_test {
static constexpr auto NUM_CASES = 5'000U;

static constexpr auto RGB_MATRIX = "resources/rgb.csv";
static constexpr auto HSV_MATRIX = "resources/hsv.csv";
static constexpr auto HSL_MATRIX = "resources/hsl.csv";

static constexpr auto ANNOUNCE_TEMPLATE = "Test {:>12} -- {:<8} passed";

void color_concepts();

void rgb_hsvl(std::span<const true_color> true_colors,
              std::span<const hsv_color> hsv_colors,
              std::span<const hsl_color> hsl_colors);

template <typename T>
concept numeric = std::unsigned_integral<T> || std::floating_point<T>;

template <typename T>
concept color_class =
    std::same_as<T, true_color> ||      // NOLINT(whitespace/indent_namespace)
    std::derived_from<T, cylindrical>;  // NOLINT(whitespace/indent_namespace)

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

  const auto from_str = [](std::string_view str) {
    T result{};
    const auto [ptr, ec] = std::from_chars(str.begin(), str.end(), result);
    if (ec != std::errc{}) {
      throw std::system_error(std::make_error_code(ec),
                              "Failed to convert numeric");
    }
    if (ptr != str.end()) {
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
