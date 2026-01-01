/*
Operations for drawing rainbows.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include "colored_string.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"

/**
 * Functor for sorting cylindrical coordinates.
 */
struct rainbow {
  /**
   * Comparison operator between cylindrical coordinates.
   * @param lhs The left coordinates to test.
   * @param rhs The right coordinates to test.
   * @return A binary predicate ordering cylindrical coordintes.
   */
  bool operator()(const cylindrical& lhs, const cylindrical& rhs) const;
};

/**
 * Utility functions for spectrums and rainbows.
 */
namespace spectrum {
/**
 * Generate a rainbow sorted cylindrical to rgb spectrum map.
 * @return An iteration over all channel combinations.
 */
template <typename T>
std::map<T, rgb_color, rainbow> generate();

/**
 * Display a sorted spectrum to cout.
 * @param cyl_to_rgb Mapping sorted by the rainbow
 * functor.
 * @param lightness Filter for only the given lightness.
 * @param min_value Filter for only greater values.
 */
template <typename T>
void display(const std::map<T, rgb_color, rainbow>& cyl_to_rgb,
             double lightness, double min_value);
}  // namespace spectrum

// TEMPLATED IMPLEMENTATIONS

template <typename T>
std::map<T, rgb_color, rainbow> spectrum::generate() {
  static_assert(std::is_convertible_v<T*, cylindrical*>,
                "Map key must be a cylindrical color type");
  std::map<T, rgb_color, rainbow> cyl_to_rgb;
  for (color_t r = 0; r < color_cast(channel::END); ++r) {
    const auto red{enum_cast<channel>(r)};
    for (color_t g = 0; g < color_cast(channel::END); ++g) {
      const auto green{enum_cast<channel>(g)};
      for (color_t b = 0; b < color_cast(channel::END); ++b) {
        const auto blue{enum_cast<channel>(b)};

        cyl_to_rgb.emplace(std::piecewise_construct,
                           std::forward_as_tuple(red, green, blue),
                           std::forward_as_tuple(red, green, blue));
      }
    }
  }
  return cyl_to_rgb;
}

template <typename T>
void spectrum::display(const std::map<T, rgb_color, rainbow>& cyl_to_rgb,
                       double lightness, double min_value) {
  static_assert(std::is_convertible_v<T*, cylindrical*>,
                "Map key must be a cylindrical color type");
  const colored_string display{std::string(2, ' ')};
  for (const auto& pr : cyl_to_rgb) {
    const auto& cyl = pr.first;
    const auto passed_filter = util::almost_eq(cyl.lightness(), lightness) &&
                               util::almost_less(min_value, cyl.value());
    if (!passed_filter) continue;
    std::cout << display.background(pr.second);
  }
  std::cout << '\n';
}
