/*
String representation of color types.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <array>
#include <iostream>
#include <limits>
#include <string_view>

#include "true_color.h"

namespace parse {
/**
 * @brief Number of digits required to represent color_t as base 10 string.
 */
static constexpr auto DIGITS = std::numeric_limits<color_t>::digits10 + 1;

/**
 * @brief Convert a color to its base 10 string representation.
 * @param buffer The array to write characters to.
 * @param col The color to convert into its string representation.
 * @return A string_view backed by buffer of the produced string.
 */
std::string_view to_str(std::array<char, DIGITS>& buffer, color_t col);

/**
 * @brief Write a string view to an output stream.
 * @param os The output stream to write to.
 * @param sv The string to write.
 */
void write_sv(std::ostream& os, std::string_view sv);
}  // namespace parse
