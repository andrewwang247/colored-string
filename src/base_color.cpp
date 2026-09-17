/*
Abstract base colors.

Copyright 2026. Andrew Wang.
*/
#include "base_color.h"

color::color(color_t offset) noexcept : m_offset(offset) {}

color::~color() noexcept = default;
