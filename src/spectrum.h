/*
Operations for drawing rainbows.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <concepts>
#include <functional>
#include <iostream>
#include <map>
#include <ranges>
#include <tuple>

#include "colored_string.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"

template <typename T>
concept cylindrical_space = std::derived_from<T, cylindrical>;

template <cylindrical_space CS>
using spectrum_map_t = std::map<CS, rgb_color, std::less<>>;

template <typename T>
concept rgb_range = std::ranges::input_range<T> &&
                    std::same_as<std::ranges::range_value_t<T>, rgb_color>;

/**
 * @brief Utility functions for spectrums and rainbows.
 */
namespace spectrum {

/**
 * @brief Generate a rainbow sorted cylindrical to rgb spectrum map.
 * @return An iteration over all channel combinations.
 */
template <cylindrical_space CS>
constexpr spectrum_map_t<CS> generate();

/**
 * @brief Filter key value pairs on the key's lightness.
 * @param lightness The lightness to epsilon equate to.
 * @return A views filter for maps with cylindrical key.
 */
constexpr auto filter_lightness(double lightness);

/**
 * @brief Filter key value pairs on the key's value.
 * @param min_value The min value to accept.
 * @return A views filter for maps with cylindrical key.
 */
constexpr auto filter_min_value(double min_value);

/**
 * @brief Display a RGB colors to stdout.
 * @param rng The input range of colors.
 */
void display(rgb_range auto&& rng);

}  // namespace spectrum

// TEMPLATED IMPLEMENTATIONS

template <cylindrical_space CS>
constexpr spectrum_map_t<CS> spectrum::generate() {
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

constexpr auto spectrum::filter_lightness(double lightness) {
  return std::views::filter([lightness](const auto& kv) constexpr {
    return util::almost_eq(lightness, kv.first.lightness());
  });
}

constexpr auto spectrum::filter_min_value(double min_value) {
  return std::views::filter([min_value](const auto& kv) constexpr {
    return min_value < kv.first.value();
  });
}

void spectrum::display(rgb_range auto&& rng) {
  colored_string display{"  "};
  for (auto&& rgb : rng) {
    std::cout << display.set_background(rgb);
  }
  std::cout << '\n';
}
