/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "bright_color.h"
#include "colored_string.h"
#include "greyscale_color.h"
#include "rgb_color.h"
#include "spectrum.h"
#include "standard_color.h"
#include "unit_test.h"
#include "util.h"

using std::cout;
using std::ios_base;
using std::map;
using std::string;
using std::to_string;

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

int main() {
  ios_base::sync_with_stdio(false);
  show_all_colors();
  paint_merica();
#ifdef DEBUG
  unit_test::hsvl();
#endif
  display_rainbows();
}

void show_color(const color& col) {
  // Pad code string to length 3
  const auto code_str{to_string(col.code())};
  const string filler_whitespace(3 - code_str.length(), ' ');
  colored_string str{filler_whitespace + code_str};
  cout << str.foreground(col);
  str.reset_foreground();
  str = "   ";
  cout << str.background(col) << ' ';
  str.reset_background();
}

void show_all_colors() {
  cout << "STANDARD COLORS:\n";
  for (color_t i = 0; i < color_cast(palette::END); ++i) {
    const auto shade = static_cast<palette>(i);
    show_color(standard_color(shade));
  }
  cout << "\n\nBRIGHT COLORS:\n";
  for (color_t j = 0; j < color_cast(palette::END); ++j) {
    const auto shade = static_cast<palette>(j);
    show_color(bright_color(shade));
  }
  cout << "\n\nRGB COLORS:";
  size_t rgb_displayed = 0;
  for (color_t r = 0; r < color_cast(channel::END); ++r) {
    const channel red{static_cast<channel>(r)};
    for (color_t g = 0; g < color_cast(channel::END); ++g) {
      const channel green{static_cast<channel>(g)};
      for (color_t b = 0; b < color_cast(channel::END); ++b) {
        const channel blue{static_cast<channel>(b)};

        if (rgb_displayed++ % color_cast(palette::END) == 0) cout << '\n';
        const rgb_color rgb{red, green, blue};
        show_color(rgb);
      }
    }
  }
  cout << "\n\nGREYSCALE COLORS:";
  for (color_t k = 0; k < color_cast(grey::END); ++k) {
    if (k % color_cast(palette::END) == 0) cout << '\n';
    const auto shade = static_cast<grey>(k);
    show_color(greyscale_color(shade));
  }
  cout << '\n';
}

void paint_merica() {
  const bright_color red(palette::RED);
  const greyscale_color white(grey::G23);
  const bright_color blue(palette::BLUE);

  const auto white_star =
      colored_string{"X"}.foreground(white).background(blue);

  const auto blue_patch = colored_string{" "}.background(blue);

  constexpr auto len_right_of_stars_patch = 26;
  const string init_strip(len_right_of_stars_patch, ' ');
  auto red_strip = colored_string{init_strip}.background(red);
  auto white_strip = colored_string{init_strip}.background(white);

  const auto star_line_red = [&blue_patch, &white_star, &red_strip]() {
    util::alternating_cout(blue_patch, white_star, 8);
    cout << blue_patch << red_strip << '\n';
  };
  const auto star_line_white = [&blue_patch, &white_star, &white_strip]() {
    cout << blue_patch << blue_patch;
    util::alternating_cout(white_star, blue_patch, 7);
    cout << blue_patch << white_strip << '\n';
  };

  cout << "\n'MERICA:\n";
  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();

  // Must go after printing lines with stars.
  // We capture by reference in lambas.
  constexpr auto len_of_stars_patch = 17;
  const string extension(len_of_stars_patch, ' ');
  red_strip += extension;
  white_strip += extension;

  for (int i = 0; i < 3; ++i) {
    cout << white_strip << '\n' << red_strip << '\n';
  }
}

void display_rainbows() {
  const auto cyl_to_rgb{spectrum::generate<hsl>()};
  cout << "\nDark rainbow:\n";
  spectrum::display(cyl_to_rgb, .3, .55);
  cout << "Standard rainbow:\n";
  spectrum::display(cyl_to_rgb, .5, .95);
  cout << "Pastel rainbow:\n";
  spectrum::display(cyl_to_rgb, .7, .95);
}
