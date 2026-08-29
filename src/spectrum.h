/*
Operations for drawing rainbows.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <iostream>
#include <map>
#include <ranges>
#include <tuple>

#include "colored_string.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"

namespace views = std::views;

/**
 * @brief Functor for sorting cylindrical coordinates.
 */
struct rainbow {
  /**
   * @brief Comparison operator between cylindrical coordinates.
   * @param lhs The left coordinates to test.
   * @param rhs The right coordinates to test.
   * @return A binary predicate ordering cylindrical coordinates.
   */
  constexpr static bool operator()(const cylindrical& lhs,
                                   const cylindrical& rhs) {
    if (!util::almost_eq(lhs.lightness(), rhs.lightness())) {
      return lhs.lightness() < rhs.lightness();
    }
    if (!util::almost_eq(lhs.hue(), rhs.hue())) {
      return lhs.hue() < rhs.hue();
    }
    if (!util::almost_eq(lhs.chroma(), rhs.chroma())) {
      return lhs.chroma() < rhs.chroma();
    }
    if (!util::almost_eq(lhs.value(), rhs.value())) {
      return lhs.value() < rhs.value();
    }
    return lhs.saturation() < rhs.saturation();
  }
};

/**
 * @brief Utility functions for spectrums and rainbows.
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
  spectrum_map_t<CS> cyl_to_rgb;
  const auto ch_rng =
      views::iota(color_cast(channel::C0), color_cast(channel::END)) |
      views::transform(
          [](auto col) static constexpr { return static_cast<channel>(col); });
  for (auto&& [r, g, b] : views::cartesian_product(ch_rng, ch_rng, ch_rng)) {
    cyl_to_rgb.emplace(std::piecewise_construct, std::forward_as_tuple(r, g, b),
                       std::forward_as_tuple(r, g, b));
  }
  return cyl_to_rgb;
}

template <cylindrical_space CS>
void spectrum::display(const spectrum_map_t<CS>& cyl_to_rgb, double lightness,
                       double min_value) {
  colored_string display{"  "};
  for (const auto& [cyl, rgb] : cyl_to_rgb) {
    if (util::almost_eq(lightness, cyl.lightness()) &&
        util::almost_less(min_value, cyl.value())) {
      std::cout << display.set_background(rgb);
    }
  }
  std::cout << '\n';
}
