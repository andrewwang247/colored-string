/*
Cylindrical coordinate color repsentations.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <stdexcept>

#include "rgb_color.h"
#include "util.h"

/**
 * Base cylindrical representation.
 */
class cylindrical {
 protected:
  double m_hue, m_chroma, m_saturation, m_value, m_lightness;

  cylindrical();
  cylindrical(channel red, channel green, channel blue);
  cylindrical(color_t red, color_t green, color_t blue);

 public:
  double hue() const noexcept;
  double chroma() const noexcept;
  double saturation() const noexcept;
  double value() const noexcept;
  double lightness() const noexcept;

 private:
  /**
   * Generic helper to compute representation.
   */
  template <typename T>
  void generic_construct(T red, T green, T blue);

 protected:
  /**
   * Set the saturation using other members.
   */
  virtual void set_saturation() = 0;
};

class hsv final : public cylindrical {
 public:
  hsv();
  hsv(channel red, channel green, channel blue);
  hsv(color_t red, color_t green, color_t blue);

 protected:
  void set_saturation() override;
};

class hsl final : public cylindrical {
 public:
  hsl();
  hsl(channel red, channel green, channel blue);
  hsl(color_t red, color_t green, color_t blue);

 protected:
  void set_saturation() override;
};

template <typename T>
void cylindrical::generic_construct(T red, T green, T blue) {
  const auto r{util::normalize(red)};
  const auto g{util::normalize(green)};
  const auto b{util::normalize(blue)};

  const auto x_max{std::max({r, g, b})};
  const auto x_min{std::min({r, g, b})};

  m_value = x_max;
  m_chroma = x_max - x_min;
  m_lightness = (x_max + x_min) / 2;

  if (util::almost_eq(m_chroma, 0.)) return;

  switch (util::var_argmax({r, g, b})) {
    case 0:  // r
      m_hue = std::fmod((g - b) / m_chroma, 6.);
      m_hue += m_hue < 0. ? 6. : 0.;
      break;
    case 1:  // g
      m_hue = 2. + (b - r) / m_chroma;
      break;
    case 2:  // b
      m_hue = 4. + (r - g) / m_chroma;
      break;
    default:
      throw std::out_of_range("Unexpected pointer difference from argmax");
  }
  m_hue = 60 * std::abs(m_hue);
}
