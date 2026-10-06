/*
Unit tests for colors and cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <cassert>
#include <compare>
#include <concepts>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <print>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "colored_string.h"
#include "hsl_color.h"
#include "hsv_color.h"
#include "parse.h"
#include "true_color.h"

using std::getline;
using std::ifstream;
using std::println;
using std::size_t;
using std::span;
using std::string;
using std::string_view;
using std::vector;

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
  const auto solutions =
      cs::unit_test::read_solutions("./resources/colors.csv", 5'000U);

  println("--- EXECUTING UNIT TESTS ---");
  cs::unit_test::color_concepts();
  cs::unit_test::rgb_hsvl(solutions);
  println("--- COMPLETED UNIT TESTS ---");
}

namespace cs {

template <typename T>
static constexpr void assert_traits() {
  static_assert(std::regular<T>);
  static_assert(std::three_way_comparable<const T>);
  static_assert(std::totally_ordered<const T>);
  static_assert(std::is_nothrow_destructible_v<const T>);
  static_assert(std::is_nothrow_move_constructible_v<T>);
  static_assert(std::is_nothrow_move_assignable_v<T>);
}

static constexpr auto RESULT_TEMPLATE = "Test {:>12} -- {:<8} passed";

void unit_test::color_concepts() {
  assert_traits<true_color>();
  static_assert(std::is_aggregate_v<true_color>);

  assert_traits<hsv_color>();
  assert_traits<hsl_color>();

  assert_traits<colored_string>();
  static_assert(std::is_aggregate_v<colored_string>);
  println(RESULT_TEMPLATE, "concepts", "color");
}

vector<unit_test::solution_t> unit_test::read_solutions(const char* name,
                                                        size_t sz) {
  using parse::from_str;

  ifstream fin{name};
  assert(fin);

  string line;
  getline(fin, line);
  static constexpr auto EXPECTED_HEADER =
      "hex,red,green,blue,hue,saturation_v,saturation_l,value,lightness";
  assert(line == EXPECTED_HEADER);

  vector<solution_t> solutions;
  solutions.reserve(sz);

  while (getline(fin, line)) {
    auto row = views::split(line, ',') | views::transform([](auto&& rng) {
                 return string_view{rng.begin(), rng.end()};
               });
    assert(ranges::distance(row) == 9);
    auto it = row.begin();

    const auto hex = string{*it++};
    const auto rgb = true_color{.red = from_str<color_t>(*it++),
                                .green = from_str<color_t>(*it++),
                                .blue = from_str<color_t>(*it++)};

    const auto hue = from_str<double>(*it++);
    const auto sat_v = from_str<double>(*it++);
    const auto sat_l = from_str<double>(*it++);

    const auto hsv = hsv_color{hue, sat_v, from_str<double>(*it++)};
    const auto hsl = hsl_color{hue, sat_l, from_str<double>(*it++)};

    assert(it == row.end());
    solutions.emplace_back(hex, rgb, hsv, hsl);
  }

  assert(solutions.size() == sz);
  println("Imported {} solutions from {}", sz, name);
  return solutions;
}

void unit_test::rgb_hsvl(span<const solution_t> solutions) {
  for (const auto& [hex, rgb, hsv, hsl] : solutions) {
    assert(~~rgb == rgb);

    assert(rgb.hex() == hex);
    assert(rgb == true_color::from_hex(hex));
    assert(rgb == true_color::from_hex(hex.substr(1)));

    const auto hsv_from_rgb = hsv_color(rgb);
    const auto hsl_from_rgb = hsl_color(rgb);
    assert(hsv == hsv_from_rgb);
    assert(hsl == hsl_from_rgb);

    const auto rgb_from_hsv = hsv.to_rgb();
    const auto rgb_from_hsl = hsl.to_rgb();
    assert(rgb == rgb_from_hsv);
    assert(rgb == rgb_from_hsl);
  }
  println(RESULT_TEMPLATE, "sRGB", "HSV/L");
}

}  // namespace cs
