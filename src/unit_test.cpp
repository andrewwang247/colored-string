/*
Unit tests for cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <cassert>
#include <fstream>
#include <print>
#include <span>

#include "base_color.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "util.h"  // NOLINT(misc-include-cleaner)

using std::ifstream;
using std::println;
using std::span;

int main() {
  const auto rgb_vec = unit_test::read_file<unsigned>(unit_test::RGB_MATRIX);
  const auto hsv_vec = unit_test::read_file<double>(unit_test::HSV_MATRIX);
  const auto hsl_vec = unit_test::read_file<double>(unit_test::HSL_MATRIX);

  println("--- EXECUTING UNIT TESTS ---");
  unit_test::rgb_color_hsvl();
  unit_test::srgb_hsvl(rgb_vec, hsv_vec, hsl_vec);
  println("--- FINISHED UNIT TESTS ---");
}

void unit_test::rgb_color_hsvl() noexcept {
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
  println(ANNOUNCE_TEMPLATE, "rgb_color -- HSV/L");
}

void unit_test::srgb_hsvl(span<const triplet<unsigned>> rgb_vec,
                          span<const triplet<double>> hsv_vec,
                          span<const triplet<double>> hsl_vec) noexcept {
  for (auto i = 0UZ; i < unit_test::NUM_CASES; ++i) {
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
  println(ANNOUNCE_TEMPLATE, "sRGB -- HSV/L");
}
