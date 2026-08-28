/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include "demo.h"

#include <cstddef>
#include <exception>
#include <format>
#include <iostream>
#include <optional>

#include "base_color.h"
#include "bright_color.h"
#include "colored_string.h"
#include "grayscale_color.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "spectrum.h"
#include "standard_color.h"

using std::cout;
using std::format;
using std::ios_base;
using std::nullopt;
using std::terminate;

int main() {
  ios_base::sync_with_stdio(false);

  demo::show_all_colors();
  demo::paint_america();
  demo::display_rainbows();
}

void demo::show_color(const color& col) {
  colored_string str{format(R"({:>3})", col.code())};
  cout << str.set_foreground(col);
  if (str.get_foreground()->code() != col.code()) terminate();
  str.reset_foreground();
  str.data_reference() = "   ";
  cout << str.set_background(col) << ' ';
  if (str.get_background()->code() != col.code()) terminate();
  str.reset_background();
}

/**
 * Demonstrate all ANSI 8-bit colors.
 */
void demo::show_all_colors() {
  cout << "Standard colors:\n";
  for (color_t i = 0; i < color_cast(palette::END); ++i) {
    const auto shade = static_cast<palette>(i);
    show_color(standard_color(shade));
  }
  cout << "\n\nBright colors:\n";
  for (color_t j = 0; j < color_cast(palette::END); ++j) {
    const auto shade = static_cast<palette>(j);
    show_color(bright_color(shade));
  }
  cout << "\n\nRGB colors:";
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
  cout << "\n\nGrayscale colors:";
  for (color_t k = 0; k < color_cast(gray::END); ++k) {
    if (k % color_cast(palette::END) == 0) cout << '\n';
    const auto shade = static_cast<gray>(k);
    show_color(grayscale_color(shade));
  }
  cout << '\n';
}

void demo::paint_america() {
  const bright_color red(palette::RED);
  const grayscale_color white(gray::G23);
  const bright_color blue(palette::BLUE);

  const colored_string white_star{"X", white, blue};
  const colored_string blue_patch{" ", nullopt, blue};

  const auto right_strip = format("{:<26}", "");
  colored_string red_strip{right_strip, nullopt, red};
  colored_string white_strip{right_strip, nullopt, white};

  const auto star_line_red = [&blue_patch, &white_star, &red_strip]() {
    for (int i = 0; i < 8; ++i) cout << blue_patch << white_star;
    cout << blue_patch << red_strip << '\n';
  };
  const auto star_line_white = [&blue_patch, &white_star, &white_strip]() {
    cout << blue_patch << blue_patch;
    for (int i = 0; i < 7; ++i) cout << white_star << blue_patch;
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

  const auto extension = format("{:<17}", "");
  red_strip.data_reference() += extension;
  white_strip.data_reference() += extension;

  for (int i = 0; i < 3; ++i) {
    cout << format("{}\n{}\n", white_strip.show(), red_strip.show());
  }
}

void demo::display_rainbows() {
  const auto cyl_to_rgb{spectrum::generate<hsl>()};
  cout << "\nDark rainbow:\n";
  spectrum::display(cyl_to_rgb, .3, .55);
  cout << "Standard rainbow:\n";
  spectrum::display(cyl_to_rgb, .5, .95);
  cout << "Pastel rainbow:\n";
  spectrum::display(cyl_to_rgb, .7, .95);
}
