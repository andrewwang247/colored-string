/*
Colored strings.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include "base_color.h"
#include "greyscale_color.h"
#include "high_intensity_color.h"
#include "rgb_color.h"
#include "standard_color.h"

/**
 * String that maintains foreground and background colors.
 */
class colored_string : public std::string {
 private:
  /**
   * Foreground color.
   */
  mutable std::unique_ptr<color> m_foreground;

  /**
   * Background color.
   */
  mutable std::unique_ptr<color> m_background;

 public:
  /**
   * Constructor for the underlying std::string.
   *
   * @param args Arguments to std::string constructor.
   */
  template <typename... Args>
  explicit colored_string(Args&&... args)
      : std::string(std::forward<Args>(args)...),
        m_foreground(nullptr),
        m_background(nullptr) {}

  template <typename... Args>
  colored_string& operator=(Args&&... args) {
    std::string::operator=(std::forward<Args>(args)...);
    return *this;
  }

  /**
   * Modify the foreground color.
   *
   * @param fore The color of the foreground.
   * @return A reference to this.
   */
  const colored_string& foreground(const color& fore) const;

  /**
   * See below.
   *
   *
   * @return Reference to foreground color.
   */
  const color& foreground() const;

  /**
   * Reset foreground color to default.
   */
  void reset_foreground() const;

  /**
   * Modify the background color.
   *
   * @param back The color of the background.
   * @return A reference to this.
   */
  const colored_string& background(const color& back) const;

  /**
   * See below.
   *
   * @return Reference to background color.
   */
  const color& background() const;

  /**
   * Reset background color to default.
   */
  void reset_background() const;

  /**
   * Print with foreground and background colors.
   */
  friend std::ostream& operator<<(std::ostream& os, const colored_string& str);
};
