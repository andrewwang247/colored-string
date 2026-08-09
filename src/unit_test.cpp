/*
Unit tests for cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "base_color.h"
#include "hsvl.h"
#include "util.h"  // NOLINT(misc-include-cleaner)

using std::cout;
using std::ifstream;
using std::ios_base;
using std::runtime_error;
using std::vector;

using unit_test::PRECISION;

template <typename T>
static vector<triplet<T>> read_file(const char* name) {
  vector<triplet<T>> data;
  data.reserve(unit_test::NUM_CASES);

  ifstream fin{name};
  if (!fin) throw runtime_error("Could not open matrix file");
  for (T a, b, c; fin >> a >> b >> c;) {
    data.emplace_back(a, b, c);
  }

  assert(data.size() == unit_test::NUM_CASES);
  return data;
}

int main() {
  ios_base::sync_with_stdio(false);

  cout << "--- EXECUTING UNIT TESTS ---\n";
  cout << "Reading RGB, HSV, and HSL matrices\n";
  const auto rgb_vec = read_file<unsigned>("test/mat_rgb.txt");
  const auto hsv_vec = read_file<double>("test/mat_hsv.txt");
  const auto hsl_vec = read_file<double>("test/mat_hsl.txt");

  cout << "Discovered " << unit_test::NUM_CASES << " test cases\n";
  cout << "Verifying that hsvl coordinates match expected\n";
  for (size_t i = 0; i < unit_test::NUM_CASES; ++i) {
    const auto& rgb_actual = rgb_vec.at(i);
    const auto r{static_cast<color_t>(rgb_actual.m_a)};
    const auto g{static_cast<color_t>(rgb_actual.m_b)};
    const auto b{static_cast<color_t>(rgb_actual.m_c)};

    const hsv hsv_actual{r, g, b};
    [[maybe_unused]] const auto& hsv_expected = hsv_vec.at(i);
    assert(util::almost_eq(hsv_actual.hue(), hsv_expected.m_a, PRECISION));
    assert(
        util::almost_eq(hsv_actual.saturation(), hsv_expected.m_b, PRECISION));
    assert(util::almost_eq(hsv_actual.value(), hsv_expected.m_c, PRECISION));

    const hsl hsl_actual{r, g, b};
    [[maybe_unused]] const auto& hsl_expected = hsl_vec.at(i);
    assert(util::almost_eq(hsl_actual.hue(), hsl_expected.m_a, PRECISION));
    assert(
        util::almost_eq(hsl_actual.saturation(), hsl_expected.m_b, PRECISION));
    assert(
        util::almost_eq(hsl_actual.lightness(), hsl_expected.m_c, PRECISION));
  }
  cout << "--- FINISHED UNIT TESTS ---\n";
}
