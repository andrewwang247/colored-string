/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <string_view>

#include "true_color.h"

namespace demo {
static constexpr auto WIDTH = 72U;

/**
 * @brief Paint the American flag.
 */
void paint_america();

/**
 * @brief Modulate hue to create rainbows.
 * @param name The name of the rainbow.
 * @param light Fixed lightness.
 */
void hue_rainbow(std::string_view name, double light);

/**
 * @brief Modulate value to create palettes.
 * @param name The name of the palette.
 * @param hue Fixed hue.
 * @param sat Fixed saturation.
 */
void value_palette(std::string_view name, double hue, double sat);
}  // namespace demo
