/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/

#pragma once
#include "base_color.h"

/**
 * Demo of colored string abilities.
 */
namespace demo {
/**
 * @brief Demonstrate col by output to std::cout.
 * @param col The color to demonstrate.
 */
void show_color(const color& col);

/**
 * @brief Demonstrate all ANSI 8-bit colors.
 */
void show_all_colors();

/**
 * @brief Paint the American flag.
 */
void paint_america();

/**
 * @brief Display rainbows to showcase cylindrical color space.
 */
void display_rainbows();
}  // namespace demo
