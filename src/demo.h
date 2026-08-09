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
 * Demonstrate col by output to std::cout.
 *
 * @param col The color to demonstrate.
 */
void show_color(const color& col);

/**
 * Demonstrate all ANSI 8-bit colors.
 */
void show_all_colors();

/**
 * Paint the American flag.
 */
void paint_merica();

/**
 * Display various rainbows, showcasing cylindricals.
 */
void display_rainbows();
}  // namespace demo
