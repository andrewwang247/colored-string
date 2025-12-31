/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include <iomanip>
#include <iostream>
#include <string>

#include "bright_color.h"
#include "colored_string.h"
#include "greyscale_color.h"
#include "rgb_color.h"
#include "standard_color.h"

using std::cout;
using std::ios_base;
using std::string;
using std::to_string;

/**
 * Demonstrate all ANSI 8-bit colors.
 */
void show_all_colors();

/**
 * Alternate printing 2 objects to std::cout.
 * @param first The first object to print.
 * @param second The second object to print.
 * @param reps Number of times to alternate.
 */
template <typename T>
void alternating_cout(const T& first, const T& second, int reps);

/**
 * Paint the American flag.
 */
void merica();

int main() {
  ios_base::sync_with_stdio(false);
  show_all_colors();
  merica();
}

/**
 * Demonstrate col by output to std::cout.
 *
 * @param col The color to demonstrate.
 */
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
  for (color_t i = 0; i < PALETTE_SIZE; ++i) {
    const auto shade = static_cast<palette>(i);
    show_color(standard_color(shade));
  }
  cout << "\n\nBRIGHT COLORS:\n";
  for (color_t j = 0; j < PALETTE_SIZE; ++j) {
    const auto shade = static_cast<palette>(j);
    show_color(bright_color(shade));
  }
  cout << "\n\nRGB COLORS:";
  size_t rgb_displayed = 0;
  for (color_t r = 0; r < RGB_CHANNELS; ++r) {
    const channel red{static_cast<channel>(r)};
    for (color_t g = 0; g < RGB_CHANNELS; ++g) {
      const channel green{static_cast<channel>(g)};
      for (color_t b = 0; b < RGB_CHANNELS; ++b) {
        const channel blue{static_cast<channel>(b)};

        if (rgb_displayed++ % PALETTE_SIZE == 0) cout << '\n';
        const rgb_color rgb{red, green, blue};
        show_color(rgb);
      }
    }
  }
  cout << "\n\nGREYSCALE COLORS:";
  for (color_t k = 0; k < SHADES_OF_GREY; ++k) {
    if (k % PALETTE_SIZE == 0) cout << '\n';
    const auto shade = static_cast<grey>(k);
    show_color(greyscale_color(shade));
  }
  cout << '\n';
}

template <typename T>
void alternating_cout(const T& left, const T& right, int reps) {
  for (int i = 0; i < reps; ++i) {
    cout << left << right;
  }
}

void merica() {
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
    alternating_cout(blue_patch, white_star, 8);
    cout << blue_patch << red_strip << '\n';
  };
  const auto star_line_white = [&blue_patch, &white_star, &white_strip]() {
    cout << blue_patch << blue_patch;
    alternating_cout(white_star, blue_patch, 7);
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
