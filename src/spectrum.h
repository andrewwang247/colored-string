/*
Operations for drawing rainbows.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <ranges>
#include <tuple>

#include "colored_string.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"

/**
 * @brief Utility functions for spectrums and rainbows.
 */
namespace spectrum {

template <cylindrical_space CS>
using spectrum_map_t = std::map<CS, rgb_color, std::less<>>;

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
  const auto ch_rng = std::views::iota(color_t{0}, color_cast(channel::END)) |
                      std::views::transform(channel_cast);
  const auto rng_cubed = std::views::cartesian_product(ch_rng, ch_rng, ch_rng);
  for (auto&& [r, g, b] : rng_cubed) {
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
        min_value < cyl.value()) {
      std::cout << display.set_background(rgb);
    }
  }
  std::cout << '\n';
}
