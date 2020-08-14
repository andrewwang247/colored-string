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
 * Demonstrate col by output to std::cout.
 *
 * @param col The color to demonstrate.
 */
void show_color(const color& col);

int main() {
  ios_base::sync_with_stdio(false);
  cout << "STANDARD COLORS:\n";
  for (color_t i = 0; i < 8; ++i) {
    const auto shade = static_cast<palette>(i);
    show_color(standard_color(shade));
  }
  cout << "\n\nHIGH INTENSITY COLORS:\n";
  for (color_t j = 0; j < 8; ++j) {
    const auto shade = static_cast<palette>(j);
    show_color(high_intensity_color(shade));
  }
  cout << "\n\nRGB COLORS:\n";
  for (color_t r = 0; r < 6; ++r) {
    for (color_t g = 0; g < 6; ++g) {
      for (color_t b = 0; b < 6; ++b) {
        show_color(rgb_color(static_cast<rgb>(r), static_cast<rgb>(g),
                             static_cast<rgb>(b)));
      }
    }
  }
  cout << "\n\nGREYSCALE COLORS:\n";
  for (color_t k = 0; k < 24; ++k) {
    const auto shade = static_cast<grey>(k);
    show_color(greyscale_color(shade));
  }
  cout << '\n';
}

void show_color(const color& col) {
  colored_string str(to_string(col.code()));
  cout << str.foreground(col);
  str.reset_foreground();
  str = "   ";
  cout << str.background(col) << ' ';
  str.reset_background();
}
