/*
Unit tests for colors and cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <cassert>
#include <compare>
#include <concepts>
#include <print>
#include <ranges>
#include <span>
#include <type_traits>

#include "colored_string.h"
#include "hsl_color.h"
#include "hsv_color.h"
#include "true_color.h"

using std::println;
using std::span;
using unit_test::read_csv;

namespace views = std::views;

int main() {
  const auto true_colors = read_csv<true_color, color_t>("resources/rgb.csv");
  const auto hsv_colors = read_csv<hsv_color, double>("resources/hsv.csv");
  const auto hsl_colors = read_csv<hsl_color, double>("resources/hsl.csv");

  println("--- EXECUTING UNIT TESTS ---");
  unit_test::color_concepts();
  unit_test::rgb_hsvl(true_colors, hsv_colors, hsl_colors);
  println("--- COMPLETED UNIT TESTS ---");
}

template <typename T>
static constexpr void assert_traits() {
  static_assert(std::regular<T>);
  static_assert(std::three_way_comparable<const T>);
  static_assert(std::totally_ordered<const T>);
  static_assert(std::is_nothrow_destructible_v<const T>);
  static_assert(std::is_nothrow_move_constructible_v<T>);
  static_assert(std::is_nothrow_move_assignable_v<T>);
}

void unit_test::color_concepts() {
  assert_traits<true_color>();
  static_assert(std::is_aggregate_v<true_color>);

  assert_traits<hsv_color>();
  assert_traits<hsl_color>();

  assert_traits<colored_string>();
  static_assert(std::is_aggregate_v<colored_string>);
  println(ANNOUNCE_TEMPLATE, "concepts", "color");
}

void unit_test::rgb_hsvl(span<const true_color> true_colors,
                         span<const hsv_color> hsv_colors,
                         span<const hsl_color> hsl_colors) {
  for (auto&& [rgb, hsv, hsl] :
       views::zip(true_colors, hsv_colors, hsl_colors)) {
    const auto hsv_from_rgb = hsv_color(rgb);
    const auto hsl_from_rgb = hsl_color(rgb);
    assert(hsv == hsv_from_rgb);
    assert(hsl == hsl_from_rgb);

    const auto rgb_from_hsv = hsv.to_rgb();
    const auto rgb_from_hsl = hsl.to_rgb();
    assert(rgb == rgb_from_hsv);
    assert(rgb == rgb_from_hsl);

    const auto rgb_from_hex = true_color::from_hex(rgb.hex());
    assert(rgb == rgb_from_hex);
  }
  println(ANNOUNCE_TEMPLATE, "sRGB", "HSV/L");
}
