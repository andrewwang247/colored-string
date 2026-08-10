/*
Unit tests for cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <cassert>
#include <fstream>
#include <stdexcept>
#include <vector>

/**
 * Triplet of 3 equal types.
 */
template <typename T>
struct triplet {
 public:
  T m_a, m_b, m_c;

  triplet(T a, T b, T c);
};

namespace unit_test {
static constexpr unsigned NUM_CASES = 5000;
static constexpr double PRECISION = 1e-1;

static constexpr auto RGB_MATRIX = "test/mat_rgb.txt";
static constexpr auto HSV_MATRIX = "test/mat_hsv.txt";
static constexpr auto HSL_MATRIX = "test/mat_hsl.txt";

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
void validate_interop();

/**
 * @brief Validate sRGB conversions to and from HSVL.
 * @param rgb_vec RGB triplets with expected values.
 * @param hsv_vec HSV triplets with expected values.
 * @param hsl_vec HSL triplets with expected values.
 */
void validate_srgb(const std::vector<triplet<unsigned>>& rgb_vec,
                   const std::vector<triplet<double>>& hsv_vec,
                   const std::vector<triplet<double>>& hsl_vec);
}  // namespace unit_test

// TEMPLATED IMPLEMENTATIONS

template <typename T>
triplet<T>::triplet(T a, T b, T c) : m_a(a), m_b(b), m_c(c) {}

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
