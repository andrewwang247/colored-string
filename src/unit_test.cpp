/*
Unit tests for cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <cassert>
#include <print>
#include <ranges>
#include <span>

#include "base_color.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"  // NOLINT(misc-include-cleaner)

using std::println;
using std::span;

namespace views = std::views;

int main() {
  const auto rgb_list = unit_test::read_file<unsigned>(unit_test::RGB_MATRIX);
  const auto hsv_list = unit_test::read_file<double>(unit_test::HSV_MATRIX);
  const auto hsl_list = unit_test::read_file<double>(unit_test::HSL_MATRIX);

  println("--- EXECUTING UNIT TESTS ---");
  unit_test::rgb_color_hsvl();
  unit_test::srgb_hsvl(rgb_list, hsv_list, hsl_list);
  println("--- COMPLETED UNIT TESTS ---");
}

void unit_test::rgb_color_hsvl() noexcept {
  const auto ch_rng = views::iota(color_t{0}, color_cast(channel::END)) |
                      views::transform(channel_cast);
  for (auto&& [r, g, b] : views::cartesian_product(ch_rng, ch_rng, ch_rng)) {
    const rgb_color rgb{r, g, b};
    const auto hsv_convert = hsv{r, g, b}.to_rgb();
    const auto hsl_convert = hsl{r, g, b}.to_rgb();
    assert(rgb.code() == hsv_convert.code());
    assert(rgb.code() == hsl_convert.code());
  }
  println(ANNOUNCE_TEMPLATE, "rgb_color", "HSV/L");
}

void unit_test::srgb_hsvl(span<const triplet<unsigned>> rgb_list,
                          span<const triplet<double>> hsv_list,
                          span<const triplet<double>> hsl_list) noexcept {
  for (auto&& [rgb_expected, hsv_expected, hsl_expected] :
       views::zip(rgb_list, hsv_list, hsl_list)) {
    const auto [r, g, b] = rgb_expected;
    const auto red{static_cast<color_t>(r)};
    const auto green{static_cast<color_t>(g)};
    const auto blue{static_cast<color_t>(b)};

    const auto [hsv_hue, hsv_saturation, hsv_value] = hsv_expected;
    const hsv hsv_actual{red, green, blue};
    assert(util::almost_eq(hsv_hue, hsv_actual.hue(), PRECISION));
    assert(util::almost_eq(hsv_saturation, hsv_actual.saturation(), PRECISION));
    assert(util::almost_eq(hsv_value, hsv_actual.value(), PRECISION));

    const auto [hsl_hue, hsl_saturation, hsl_lightness] = hsl_expected;
    const hsl hsl_actual{red, green, blue};
    assert(util::almost_eq(hsl_hue, hsl_actual.hue(), PRECISION));
    assert(util::almost_eq(hsl_saturation, hsl_actual.saturation(), PRECISION));
    assert(util::almost_eq(hsl_lightness, hsl_actual.lightness(), PRECISION));

    // Validate epsilon equality operator.
    assert(hsv_actual == hsl_actual);
  }
  println(ANNOUNCE_TEMPLATE, "sRGB", "HSV/L");
}
