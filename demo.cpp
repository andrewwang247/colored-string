/*
Colorful string demo.

Copyright 2020. Siwei Wang.
*/
#include <iostream>
#include "colored_string.h"
using std::cout;
using std::ios_base;
using std::to_string;

/**
 * Demonstrate this color.
 */
void show_color(const color& col);

/**
 * Demonstrate all colors.
 */
void show_all();

int main() {
  ios_base::sync_with_stdio(false);
  show_all();
  const rgb_color amazon_fore(255_c, 135_c, 0_c);
  const rgb_color amazon_back(20_c, 110_c, 180_c);
  colored_string az("I work at Amazon!");
  az.foreground(amazon_fore).background(amazon_back);
  cout << az << '\n';
}

void show_color(const color& col) {
  colored_string str("FORE");
  cout << +col.code() << '\t';
  cout << str.foreground(col) << " -- ";
  str.reset_foreground();
  str = "BACK";
  cout << str.background(col) << '\n';
  str.reset_background();
}

void show_all() {
  cout << "STANDARD COLORS:\n";
  for (color_t i = 0; i < 8; ++i) {
    const auto shade = static_cast<palette>(i);
    show_color(standard_color(shade));
  }
  cout << "HIGH INTENSITY COLORS:\n";
  for (color_t j = 0; j < 8; ++j) {
    const auto shade = static_cast<palette>(j);
    show_color(high_intensity_color(shade));
  }
  cout << "RGB COLORS:\n";
  for (color_t r = 0; r < 6; ++r) {
    for (color_t g = 0; g < 6; ++g) {
      for (color_t b = 0; b < 6; ++b) {
        show_color(rgb_color(static_cast<rgb>(r), static_cast<rgb>(g),
                             static_cast<rgb>(b)));
      }
    }
  }
  cout << "GREYSCALE COLORS:\n";
  for (color_t k = 0; k < 24; ++k) {
    const auto shade = static_cast<grey>(k);
    show_color(greyscale_color(shade));
  }
}
