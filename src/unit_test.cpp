/*
Unit tests for cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#include "unit_test.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "hsvl.h"
#include "util.h"

using std::cout;
using std::ifstream;
using std::runtime_error;
using std::string;
using std::vector;

template <typename T>
vector<triplet<T>> read_file(string name) {
  vector<triplet<T>> data;
  data.reserve(unit_test::NUM_CASES);

  ifstream fin{name};
  if (!fin) throw runtime_error("Could not open matrix file");
  for (T a, b, c; fin >> a >> b >> c;) {
    data.emplace_back(a, b, c);
  }
  return data;
}

void unit_test::hsvl() {
  cout << "\n--- EXECUTING UNIT TESTS ---\n";
  cout << "Reading RGB, HSV, and HSL matrices\n";
  const auto rgb_vec = read_file<unsigned>("test/mat_rgb.txt");
  const auto hsv_vec = read_file<double>("test/mat_hsv.txt");
  const auto hsl_vec = read_file<double>("test/mat_hsl.txt");

  cout << "Discovered " << NUM_CASES << " test cases\n";
  cout << "Verifying that hsvl coordinates match expected\n";
  for (size_t i = 0; i < NUM_CASES; ++i) {
    const auto r{static_cast<color_t>(rgb_vec[i].m_a)};
    const auto g{static_cast<color_t>(rgb_vec[i].m_b)};
    const auto b{static_cast<color_t>(rgb_vec[i].m_c)};

    const hsv hsv_actual{r, g, b};
    assert(util::almost_eq(hsv_actual.hue(), hsv_vec[i].m_a, PRECISION));
    assert(util::almost_eq(hsv_actual.saturation(), hsv_vec[i].m_b, PRECISION));
    assert(util::almost_eq(hsv_actual.value(), hsv_vec[i].m_c, PRECISION));

    const hsl hsl_actual{r, g, b};
    assert(util::almost_eq(hsl_actual.hue(), hsl_vec[i].m_a, PRECISION));
    assert(util::almost_eq(hsl_actual.saturation(), hsl_vec[i].m_b, PRECISION));
    assert(util::almost_eq(hsl_actual.lightness(), hsl_vec[i].m_c, PRECISION));
  }
  cout << "--- FINISHED UNIT TESTS ---\n";
}
