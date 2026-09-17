/*
Unit tests for color and cylindrical.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <fstream>
#include <functional>
#include <ranges>
#include <span>
#include <vector>

/**
 * @brief Triplet of 3 equal types.
 */
template <typename T>
struct triplet {
 public:
  T m_a, m_b, m_c;

  triplet(T a, T b, T c) noexcept;
};

/**
 * @brief Unit testing.
 */
namespace unit_test {
static constexpr auto NUM_CASES = 5'000UZ;
static constexpr auto PRECISION = 1e-1;

static constexpr auto RGB_MATRIX = "test/mat_rgb.txt";
static constexpr auto HSV_MATRIX = "test/mat_hsv.txt";
static constexpr auto HSL_MATRIX = "test/mat_hsl.txt";

static constexpr auto ANNOUNCE_TEMPLATE = "Test {:>12} -- {:<8} passed";

/**
 * @brief Read triplets from a file.
 * @param name The file name.
 * @return A list of triplets.
 */
template <typename T>
static std::vector<triplet<T>> read_file(const char* name);

/**
 * @brief Validate conversions between RGB and HSVL.
 */
void rgb_color_hsvl();

/**
 * @brief Validate sRGB conversions to and from HSVL.
 * @param rgb_list RGB triplets with expected values.
 * @param hsv_list HSV triplets with expected values.
 * @param hsl_list HSL triplets with expected values.
 */
void srgb_hsvl(std::span<const triplet<unsigned>> rgb_list,
               std::span<const triplet<double>> hsv_list,
               std::span<const triplet<double>> hsl_list);

/**
 * @brief Validate comparison of color types.
 */
void color_compare();

// HELPER FUNCTIONS

/**
 * @brief Validate that a range is sorted and strictly increasing.
 * @param items The range to validate.
 * @param proj Optional projection for items in range.
 * @return Whether proj(items[i]) < proj(items[j]) whenever i < j.
 */
template <typename Proj = std::identity>
bool is_strictly_ascending(std::ranges::random_access_range auto&& items,
                           Proj proj = {});

/**
 * @brief Validate that a range is sorted and strictly decreasing.
 * @param items The range to validate.
 * @param proj Optional projection for items in range.
 * @return Whether proj(items[i]) > proj(items[j]) whenever i < j.
 */
template <typename Proj = std::identity>
bool is_strictly_descending(std::ranges::random_access_range auto&& items,
                            Proj proj = {});

}  // namespace unit_test

// TEMPLATED IMPLEMENTATIONS

template <typename T>
triplet<T>::triplet(T a, T b, T c) noexcept : m_a(a), m_b(b), m_c(c) {}

template <typename T>
static std::vector<triplet<T>> unit_test::read_file(const char* name) {
  std::vector<triplet<T>> data;
  data.reserve(NUM_CASES);

  std::ifstream fin{name};
  if (!fin) throw std::runtime_error("Could not open matrix file");
  for (T a, b, c; fin >> a >> b >> c;) {
    data.emplace_back(a, b, c);
  }

  assert(data.size() == NUM_CASES);
  return data;
}

template <typename Proj>
bool unit_test::is_strictly_ascending(
    std::ranges::random_access_range auto&& items, Proj proj) {
  return std::ranges::adjacent_find(items, std::ranges::greater_equal{},
                                    proj) == items.end();
}

template <typename Proj>
bool unit_test::is_strictly_descending(
    std::ranges::random_access_range auto&& items, Proj proj) {
  return std::ranges::adjacent_find(items, std::ranges::less_equal{}, proj) ==
         items.end();
}
