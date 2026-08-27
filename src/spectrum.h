/*
Operations for drawing rainbows.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <iostream>
#include <map>
#include <tuple>

#include "colored_string.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"

/**
 * Functor for sorting cylindrical coordinates.
 */
struct rainbow {
  /**
   * @brief Comparison operator between cylindrical coordinates.
   * @param lhs The left coordinates to test.
   * @param rhs The right coordinates to test.
   * @return A binary predicate ordering cylindrical coordinates.
   */
  bool operator()(const cylindrical& lhs, const cylindrical& rhs) const;
};

/**
 * Utility functions for spectrums and rainbows.
 */
namespace spectrum {

template <cylindrical_space CS>
using spectrum_map_t = std::map<CS, rgb_color, rainbow>;

/**
 * @brief Generate a rainbow sorted cylindrical to rgb spectrum map.
 * @return An iteration over all channel combinations.
 */
template <cylindrical_space CS>
spectrum_map_t<CS> generate();

/**
 * @brief Display a sorted spectrum to cout.
 * @param cyl_to_rgb Map sorted by rainbow functor.
 * @param lightness Filter for only the given lightness.
 * @param min_value Filter for only greater values.
 */
template <cylindrical_space CS>
void display(const spectrum_map_t<CS>& cyl_to_rgb, double lightness,
             double min_value);
}  // namespace spectrum

// TEMPLATED IMPLEMENTATIONS

template <cylindrical_space CS>
spectrum::spectrum_map_t<CS> spectrum::generate() {
  constexpr color_t channel_max{color_cast(channel::END)};
  spectrum_map_t<CS> cyl_to_rgb;
  for (color_t r = 0; r < channel_max; ++r) {
    const auto red{static_cast<channel>(r)};
    for (color_t g = 0; g < channel_max; ++g) {
      const auto green{static_cast<channel>(g)};
      for (color_t b = 0; b < channel_max; ++b) {
        const auto blue{static_cast<channel>(b)};
        cyl_to_rgb.emplace(std::piecewise_construct,
                           std::forward_as_tuple(red, green, blue),
                           std::forward_as_tuple(red, green, blue));
      }
    }
  }
  return cyl_to_rgb;
}

template <cylindrical_space CS>
void spectrum::display(const spectrum_map_t<CS>& cyl_to_rgb, double lightness,
                       double min_value) {
  static const colored_string display{"  "};
  for (const auto& [cyl, rgb] : cyl_to_rgb) {
    if (util::almost_eq(lightness, cyl.lightness()) &&
        util::almost_less(min_value, cyl.value())) {
      std::cout << display.background(rgb);
    }
  }
  std::cout << '\n';
}
