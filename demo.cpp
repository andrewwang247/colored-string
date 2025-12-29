/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include <iostream>

#include "bright_color.h"
#include "colored_string.h"
#include "greyscale_color.h"
#include "rgb_color.h"
#include "standard_color.h"

using std::cout;
using std::ios_base;
using std::to_string;

/**
 * Demonstrate all ANSI 8-bit colors.
 */
void show_all();

/**
 * Paint the American flag.
 */
void merica();

int main() {
  ios_base::sync_with_stdio(false);
  show_all();
  merica();
}

/**
 * Demonstrate col by output to std::cout.
 *
 * @param col The color to demonstrate.
 */
void show_color(const color& col) {
  colored_string str(to_string(col.code()));
  cout << str.foreground(col);
  str.reset_foreground();
  str = "   ";
  cout << str.background(col) << ' ';
  str.reset_background();
}

void show_all() {
  cout << "STANDARD COLORS:\n";
  for (color_t i = 0; i < 8; ++i) {
    const auto shade = static_cast<palette>(i);
    show_color(standard_color(shade));
  }
  cout << "\n\nBRIGHT COLORS:\n";
  for (color_t j = 0; j < 8; ++j) {
    const auto shade = static_cast<palette>(j);
    show_color(bright_color(shade));
  }
  cout << "\n\nRGB COLORS:\n";
  for (color_t r = 0; r < 6; ++r) {
    for (color_t g = 0; g < 6; ++g) {
      for (color_t b = 0; b < 6; ++b) {
        show_color(rgb_color(static_cast<channel>(r), static_cast<channel>(g),
                             static_cast<channel>(b)));
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

void merica() {
  const bright_color red(palette::RED);
  const greyscale_color white(grey::G23);
  const bright_color blue(palette::BLUE);

  const auto white_patch =
      colored_string{"X"}.foreground(white).background(blue);

  const auto blue_patch = colored_string{" "}.background(blue);

  const auto init_strip = "                        ";
  auto red_strip = colored_string{init_strip}.background(red);
  auto white_strip = colored_string{init_strip}.background(white);

  cout << "\n'MERICA:\n";
  const auto star_line_red = [&blue_patch, &white_patch, &red_strip]() {
    cout << blue_patch << white_patch << blue_patch << white_patch << blue_patch
         << white_patch << blue_patch << white_patch << blue_patch
         << white_patch << blue_patch << white_patch << blue_patch
         << white_patch << blue_patch << white_patch << blue_patch << red_strip
         << '\n';
  };
  const auto star_line_white = [&blue_patch, &white_patch, &white_strip]() {
    cout << blue_patch << blue_patch << white_patch << blue_patch << white_patch
         << blue_patch << white_patch << blue_patch << white_patch << blue_patch
         << white_patch << blue_patch << white_patch << blue_patch
         << white_patch << blue_patch << blue_patch << white_strip << '\n';
  };

  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();

  const auto extension = "                 ";
  red_strip += extension;
  white_strip += extension;

  const auto strip_line_red = [&red_strip]() { cout << red_strip << '\n'; };
  const auto strip_line_white = [&white_strip]() {
    cout << white_strip << '\n';
  };

  strip_line_white();
  strip_line_red();
  strip_line_white();
  strip_line_red();
  strip_line_white();
  strip_line_red();
}
