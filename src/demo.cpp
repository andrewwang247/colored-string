/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include "demo.h"

#include <exception>
#include <format>
#include <iostream>
#include <optional>
#include <print>
#include <ranges>

#include "base_color.h"
#include "bright_color.h"
#include "colored_string.h"
#include "grayscale_color.h"
#include "hsvl.h"
#include "rgb_color.h"
#include "singular_color.h"
#include "spectrum.h"
#include "standard_color.h"

using std::cout;
using std::format;
using std::nullopt;
using std::print;
using std::println;
using std::terminate;

namespace views = std::views;

int main() {
  demo::show_all_colors();
  demo::paint_america();
  demo::display_rainbows();
}

void demo::show_color(const color& col) {
  colored_string str{format("{:>3}", col.code())};
  cout << str.set_foreground(col);
  if (str.get_foreground()->code() != col.code()) terminate();
  str.reset_foreground();
  str.data_reference() = "   ";
  cout << str.set_background(col) << ' ';
  if (str.get_background()->code() != col.code()) terminate();
  str.reset_background();
}

void demo::show_all_colors() {
  const auto palette_rng = views::iota(color_t{0}, color_cast(palette::END)) |
                           views::transform(palette_cast);

  println("Standard colors:");
  for (auto shade : palette_rng) {
    show_color(standard_color{shade});
  }
  print("\n\n");

  println("Bright colors:");
  for (auto shade : palette_rng) {
    show_color(bright_color{shade});
  }
  print("\n\n");

  println("RGB colors:");
  const auto ch_rng = views::iota(color_t{0}, color_cast(channel::END)) |
                      views::transform(channel_cast);
  const auto rgb_chunks = views::cartesian_product(ch_rng, ch_rng, ch_rng) |
                          views::chunk(color_cast(palette::END));
  for (auto&& chunk : rgb_chunks) {
    for (auto&& [r, g, b] : chunk) {
      show_color(rgb_color{r, g, b});
    }
    cout.put('\n');
  }
  cout.put('\n');

  println("Grayscale colors:");
  const auto gray_chunks = views::iota(color_t{0}, color_cast(gray::END)) |
                           views::chunk(color_cast(palette::END));
  for (auto&& chunk : gray_chunks) {
    for (auto shade : chunk | views::transform(gray_cast)) {
      show_color(grayscale_color{shade});
    }
    cout.put('\n');
  }
  cout.put('\n');
}

void demo::paint_america() {
  const bright_color red(palette::RED);
  const grayscale_color white(gray::G23);
  const bright_color blue(palette::BLUE);

  const colored_string white_star{"X", white, blue};
  const colored_string blue_patch{" ", nullopt, blue};

  const auto right_strip = format("{:26}", "");
  colored_string red_strip{right_strip, nullopt, red};
  colored_string white_strip{right_strip, nullopt, white};

  const auto star_line_red = [&blue_patch, &white_star, &red_strip]() {
    for (auto i = 0; i < 8; ++i) cout << blue_patch << white_star;
    cout << blue_patch << red_strip << '\n';
  };
  const auto star_line_white = [&blue_patch, &white_star, &white_strip]() {
    cout << blue_patch << blue_patch;
    for (auto i = 0; i < 7; ++i) cout << white_star << blue_patch;
    cout << blue_patch << white_strip << '\n';
  };

  println("'MERICA:");
  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();

  const auto extension = format("{:17}", "");
  red_strip.data_reference() += extension;
  white_strip.data_reference() += extension;

  for (auto i = 0; i < 3; ++i) {
    println("{}", white_strip.show());
    println("{}", red_strip.show());
  }
  cout.put('\n');
}

void demo::display_rainbows() {
  const auto cyl_to_rgb{spectrum::generate<hsl>()};
  println("Dark rainbow:");
  spectrum::display(cyl_to_rgb, .3, .55);
  println("Standard rainbow:");
  spectrum::display(cyl_to_rgb, .5, .95);
  println("Pastel rainbow:");
  spectrum::display(cyl_to_rgb, .7, .95);
}
