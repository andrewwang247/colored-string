/*
Unit tests for cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <cassert>
#include <cstddef>
#include <format>
#include <fstream>
#include <iostream>
#include <span>

#include "base_color.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"  // NOLINT(misc-include-cleaner)

using std::cout;
using std::format;
using std::ifstream;
using std::ios_base;
using std::span;

int main() {
  ios_base::sync_with_stdio(false);
  const auto rgb_vec = unit_test::read_file<unsigned>(unit_test::RGB_MATRIX);
  const auto hsv_vec = unit_test::read_file<double>(unit_test::HSV_MATRIX);
  const auto hsl_vec = unit_test::read_file<double>(unit_test::HSL_MATRIX);

  cout << "--- EXECUTING UNIT TESTS ---\n";
  unit_test::rgb_color_hsvl();
  unit_test::srgb_hsvl(rgb_vec, hsv_vec, hsl_vec);
  cout << "--- FINISHED UNIT TESTS ---\n";
}

void unit_test::rgb_color_hsvl() {
  constexpr color_t channel_max{color_cast(channel::END)};
  for (color_t r = 0; r < channel_max; ++r) {
    const auto red{static_cast<channel>(r)};
    for (color_t g = 0; g < channel_max; ++g) {
      const auto green{static_cast<channel>(g)};
      for (color_t b = 0; b < channel_max; ++b) {
        const auto blue{static_cast<channel>(b)};

        const rgb_color rgb{red, green, blue};
        const auto hsv_convert = hsv{red, green, blue}.to_rgb();
        const auto hsl_convert = hsl{red, green, blue}.to_rgb();
        assert(rgb.code() == hsv_convert.code());
        assert(rgb.code() == hsl_convert.code());
      }
    }
  }
  cout << format(ANNOUNCE_TEMPLATE, "rgb_color -- HSV/L");
}

void unit_test::srgb_hsvl(span<const triplet<unsigned>> rgb_vec,
                          span<const triplet<double>> hsv_vec,
                          span<const triplet<double>> hsl_vec) {
  for (size_t i = 0; i < unit_test::NUM_CASES; ++i) {
    const auto& rgb_actual = rgb_vec[i];  // NOLINT
    const auto r{static_cast<color_t>(rgb_actual.m_a)};
    const auto g{static_cast<color_t>(rgb_actual.m_b)};
    const auto b{static_cast<color_t>(rgb_actual.m_c)};

    const hsv hsv_actual{r, g, b};
    [[maybe_unused]] const auto& hsv_expected = hsv_vec[i];  // NOLINT
    assert(util::almost_eq(hsv_actual.hue(), hsv_expected.m_a, PRECISION));
    assert(
        util::almost_eq(hsv_actual.saturation(), hsv_expected.m_b, PRECISION));
    assert(util::almost_eq(hsv_actual.value(), hsv_expected.m_c, PRECISION));

    const hsl hsl_actual{r, g, b};
    [[maybe_unused]] const auto& hsl_expected = hsl_vec[i];  // NOLINT
    assert(util::almost_eq(hsl_actual.hue(), hsl_expected.m_a, PRECISION));
    assert(
        util::almost_eq(hsl_actual.saturation(), hsl_expected.m_b, PRECISION));
    assert(
        util::almost_eq(hsl_actual.lightness(), hsl_expected.m_c, PRECISION));
  }
  cout << format(ANNOUNCE_TEMPLATE, "sRGB -- HSV/L");
}
