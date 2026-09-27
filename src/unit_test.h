/*
Unit tests for colors and cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <cstddef>
#include <span>
#include <string>
#include <vector>

#include "cylindrical.h"
#include "hsl_color.h"
#include "hsv_color.h"
#include "true_color.h"

namespace cs::unit_test {

/**
 * @brief Verify that types match compile time traits.
 */
void color_concepts();

/**
 * @brief Solution to color coordinate conversion.
 */
struct solution_t {
  std::string hex;
  true_color rgb;
  hsv_color hsv;
  hsl_color hsl;
};

/**
 * @brief Read solutions from CSV file.
 * @param name The path to the file.
 * @param sz The expected number of rows.
 * @returns A list of conversion solutions.
 */
std::vector<solution_t> read_solutions(const char* name, std::size_t sz);

/**
 * @brief Test conversions between true_color and cylindrical types.
 * @param solutions The expected conversion values.
 */
void rgb_hsvl(std::span<const solution_t> solutions);

}  // namespace cs::unit_test
