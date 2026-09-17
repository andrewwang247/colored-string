/*
Unit tests for color and cylindrical.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <print>
#include <ranges>
#include <span>
#include <utility>
#include <vector>

#include "base_color.h"
#include "bright_color.h"
#include "grayscale_color.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "singular_color.h"
#include "standard_color.h"
#include "util.h"  // NOLINT(misc-include-cleaner)

using std::make_unique;
using std::println;
using std::span;
using std::unique_ptr;
using std::vector;
using util::almost_eq;

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
  const auto rgb_list = unit_test::read_file<unsigned>(unit_test::RGB_MATRIX);
  const auto hsv_list = unit_test::read_file<double>(unit_test::HSV_MATRIX);
  const auto hsl_list = unit_test::read_file<double>(unit_test::HSL_MATRIX);

  println("--- EXECUTING UNIT TESTS ---");
  unit_test::rgb_color_hsvl();
  unit_test::srgb_hsvl(rgb_list, hsv_list, hsl_list);
  unit_test::color_compare();
  println("--- COMPLETED UNIT TESTS ---");
}

void unit_test::rgb_color_hsvl() {
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
                          span<const triplet<double>> hsl_list) {
  for (auto&& [rgb_expected, hsv_expected, hsl_expected] :
       views::zip(rgb_list, hsv_list, hsl_list)) {
    const auto [r, g, b] = rgb_expected;
    const auto red{static_cast<color_t>(r)};
    const auto green{static_cast<color_t>(g)};
    const auto blue{static_cast<color_t>(b)};

    const auto [hsv_hue, hsv_saturation, hsv_value] = hsv_expected;
    const hsv hsv_actual{red, green, blue};
    assert(almost_eq(hsv_hue, hsv_actual.hue(), PRECISION));
    assert(almost_eq(hsv_saturation, hsv_actual.saturation(), PRECISION));
    assert(almost_eq(hsv_value, hsv_actual.value(), PRECISION));

    const auto [hsl_hue, hsl_saturation, hsl_lightness] = hsl_expected;
    const hsl hsl_actual{red, green, blue};
    assert(almost_eq(hsl_hue, hsl_actual.hue(), PRECISION));
    assert(almost_eq(hsl_saturation, hsl_actual.saturation(), PRECISION));
    assert(almost_eq(hsl_lightness, hsl_actual.lightness(), PRECISION));

    // Validate epsilon equality operator.
    assert(hsv_actual == hsl_actual);
  }
  println(ANNOUNCE_TEMPLATE, "sRGB", "HSV/L");
}

void unit_test::color_compare() {
  vector<unique_ptr<color>> all_colors;
  all_colors.reserve(1 << 8);

  // Construct sorted ranges for each set of colors.

  vector<standard_color> standards;
  constexpr auto palette_end = color_cast(palette::END);
  standards.reserve(palette_end);
  const auto palette_rng =
      views::iota(color_t{0}, palette_end) | views::transform(palette_cast);
  for (auto shade : palette_rng) {
    auto ptr = make_unique<standard_color>(shade);
    all_colors.emplace_back(std::move(ptr));
    standards.emplace_back(shade);
  }

  vector<bright_color> brights;
  brights.reserve(palette_end);
  for (auto shade : palette_rng) {
    auto ptr = make_unique<bright_color>(shade);
    all_colors.emplace_back(std::move(ptr));
    brights.emplace_back(shade);
  }

  vector<rgb_color> rgbs;
  constexpr auto ch_end = color_cast(channel::END);
  constexpr auto ch_num = ch_end * ch_end * ch_end;
  rgbs.reserve(ch_num);
  const auto ch_rng =
      views::iota(color_t{0}, ch_end) | views::transform(channel_cast);
  const auto rgb_rng = views::cartesian_product(ch_rng, ch_rng, ch_rng);
  for (auto&& [r, g, b] : rgb_rng) {
    auto ptr = make_unique<rgb_color>(r, g, b);
    all_colors.emplace_back(std::move(ptr));
    rgbs.emplace_back(r, g, b);
  }

  vector<grayscale_color> grays;
  constexpr auto gray_end = color_cast(gray::END);
  grays.reserve(gray_end);
  const auto gray_rng =
      views::iota(color_t{0}, gray_end) | views::transform(gray_cast);
  for (auto shade : gray_rng) {
    auto ptr = make_unique<grayscale_color>(shade);
    all_colors.emplace_back(std::move(ptr));
    grays.emplace_back(shade);
  }

  const auto deref = [](const auto& ptr) -> const color& {
    assert(ptr);
    return *ptr;
  };
  const auto color_slice = [&all_colors](auto drop, auto take) {
    return all_colors | views::drop(drop) | views::take(take);
  };

  assert(is_strictly_ascending(all_colors, deref));
  assert(is_strictly_descending(all_colors | views::reverse, deref));

  assert(ranges::equal(color_slice(0, palette_end), standards, {}, deref));
  assert(is_strictly_ascending(standards));
  assert(is_strictly_descending(standards | views::reverse));

  assert(
      ranges::equal(color_slice(palette_end, palette_end), brights, {}, deref));
  assert(is_strictly_ascending(brights));
  assert(is_strictly_descending(brights | views::reverse));

  assert(ranges::equal(color_slice(2 * palette_end, ch_num), rgbs, {}, deref));
  assert(is_strictly_ascending(rgbs));
  assert(is_strictly_descending(rgbs | views::reverse));

  assert(ranges::equal(color_slice(2 * palette_end + ch_num, gray_end), grays,
                       {}, deref));
  assert(is_strictly_ascending(grays));
  assert(is_strictly_descending(grays | views::reverse));

  assert(standards.back() < brights.front());
  assert(brights.back() < rgbs.front());
  assert(rgbs.back() < grays.front());

  println(ANNOUNCE_TEMPLATE, "color", "<=>");
}
