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
  println("--- FINISHED UNIT TESTS ---");
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
  println(ANNOUNCE_TEMPLATE, "rgb_color -- HSV/L");
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

    {
      const auto [h, s, v] = hsv_expected;
      const hsv actual{red, green, blue};
      assert(util::almost_eq(h, actual.hue(), PRECISION));
      assert(util::almost_eq(s, actual.saturation(), PRECISION));
      assert(util::almost_eq(v, actual.value(), PRECISION));
    }

    {
      const auto [h, s, l] = hsl_expected;
      const hsl actual{red, green, blue};
      assert(util::almost_eq(h, actual.hue(), PRECISION));
      assert(util::almost_eq(s, actual.saturation(), PRECISION));
      assert(util::almost_eq(l, actual.lightness(), PRECISION));
    }
  }
  println(ANNOUNCE_TEMPLATE, "sRGB -- HSV/L");
}
