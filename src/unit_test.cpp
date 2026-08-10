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
#include "rgb_color.h"
#include "util.h"  // NOLINT(misc-include-cleaner)

using std::cout;
using std::ifstream;
using std::ios_base;
using std::runtime_error;
using std::vector;

using unit_test::PRECISION;

/**
 * Read triplets from a file.
 * @param name The file name.
 * @return A list of triplets.
 */
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

/**
 * Validate conversions between RGB and HSVL.
 */
static void validate_interop() {
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
}

int main() {
  ios_base::sync_with_stdio(false);

  cout << "--- EXECUTING UNIT TESTS ---\n";
  cout << "Validating channel conversion interoperability\n";
  validate_interop();
  cout << "All RGB - HSVL channel conversions match\n";

  const auto rgb_vec = read_file<unsigned>("test/mat_rgb.txt");
  const auto hsv_vec = read_file<double>("test/mat_hsv.txt");
  const auto hsl_vec = read_file<double>("test/mat_hsl.txt");

  cout << "Discovered " << unit_test::NUM_CASES << " sRGB space test cases\n";
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
  cout << "Verified that all coordinate triplets match\n"
       << "--- FINISHED UNIT TESTS ---\n";
}
