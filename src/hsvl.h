/*
Cylindrical coordinate color repsentations.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <exception>
#include <utility>

#include "rgb_color.h"
#include "util.h"

/**
 * Base cylindrical representation.
 */
class cylindrical {
 protected:
  double m_hue = 0., m_chroma = 0., m_saturation = 0., m_value = 0.,
         m_lightness = 0.;

  cylindrical(channel red, channel green, channel blue) noexcept;
  cylindrical(color_t red, color_t green, color_t blue) noexcept;

 public:
  double hue() const noexcept;
  double chroma() const noexcept;
  double saturation() const noexcept;
  double value() const noexcept;
  double lightness() const noexcept;

  /**
   * @brief Compute the closest ANSI RGB color to this.
   * @return ANSI RGB approximation.
   */
  virtual rgb_color to_rgb() const noexcept = 0;

  virtual ~cylindrical() = default;

 private:
  /**
   * @brief Generic helper to compute representation.
   */
  template <color_specifier T>
  void generic_construct(T red, T green, T blue) noexcept;

 protected:
  /**
   * @brief Set the saturation using other members.
   */
  virtual void set_saturation() noexcept = 0;
};

template <typename T>
concept cylindrical_space = std::derived_from<T, cylindrical>;

class hsv final : public cylindrical {
 public:
  hsv(channel red, channel green, channel blue) noexcept;
  hsv(color_t red, color_t green, color_t blue) noexcept;

  rgb_color to_rgb() const noexcept override;

 protected:
  void set_saturation() noexcept override;
};

class hsl final : public cylindrical {
 public:
  hsl(channel red, channel green, channel blue) noexcept;
  hsl(color_t red, color_t green, color_t blue) noexcept;

  rgb_color to_rgb() const noexcept override;

 protected:
  void set_saturation() noexcept override;
};

template <color_specifier T>
void cylindrical::generic_construct(T red, T green, T blue) noexcept {
  const auto r{util::normalize(red)};
  const auto g{util::normalize(green)};
  const auto b{util::normalize(blue)};
  const auto rgb_list = {r, g, b};

  const auto x_max{std::max(rgb_list)};
  const auto x_min{std::min(rgb_list)};

  m_value = x_max;
  m_chroma = x_max - x_min;
  // Avoid unsigned char overflow when computing midpoint
  m_lightness = x_min + (x_max - x_min) / 2;

  if (util::almost_eq(m_chroma, 0.)) return;

  const auto max_iter = std::ranges::max_element(rgb_list);
  const auto var_argmax = std::distance(rgb_list.begin(), max_iter);

  switch (var_argmax) {
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
      std::unreachable();
  }
  m_hue = 60 * std::abs(m_hue);
}
