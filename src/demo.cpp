/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include "demo.h"

#include <iostream>
#include <iterator>
#include <print>
#include <ranges>
#include <string>

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
using std::print;
using std::println;
using std::to_string;

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
  demo::show_all_colors();
  demo::paint_america();
  demo::display_rainbows();
}

void demo::show_color(const color& col) {
  auto str = colored_string{to_string(col.code())};
  print("{:>3}", str.set_foreground(col));
  str.reset_foreground();
  str.data_reference().clear();
  print("{:3}", str.set_background(col));
  str.reset_background();
  cout.put(' ');
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
                           views::transform(gray_cast) |
                           views::chunk(color_cast(palette::END));
  for (auto&& chunk : gray_chunks) {
    for (auto shade : chunk) {
      show_color(grayscale_color{shade});
    }
    cout.put('\n');
  }
  cout.put('\n');
}

void demo::paint_america() {
  const auto red = bright_color{palette::RED};
  const auto white = grayscale_color{gray::G23};
  const auto blue = bright_color{palette::BLUE};

  const auto white_star = colored_string::builder()
                              .data("X")
                              .foreground(white)
                              .background(blue)
                              .build();
  const auto blue_patch = colored_string::builder().background(blue).build();
  const auto red_patch = colored_string::builder().background(red).build();
  const auto white_patch = colored_string::builder().background(white).build();

  const auto star_line_red = [&blue_patch, &white_star, &red_patch]() {
    for (auto i = 0; i < 8; ++i) print("{:1}{}", blue_patch, white_star);
    println("{:1}{:26}", blue_patch, red_patch);
  };
  const auto star_line_white = [&blue_patch, &white_star, &white_patch]() {
    print("{:2}", blue_patch);
    for (auto i = 0; i < 7; ++i) print("{}{:1}", white_star, blue_patch);
    println("{:1}{:26}", blue_patch, white_patch);
  };

  println("'MERICA:");
  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();
  star_line_white();
  star_line_red();

  for (auto i = 0; i < 3; ++i) {
    println("{:43}", white_patch);
    println("{:43}", red_patch);
  }
  cout.put('\n');
}

void demo::display_rainbows() {
  const auto cyl_to_rgb{spectrum::generate<hsl>()};
  auto display = colored_string{"  "};

  const auto show_rb = [&](const char* name, gray shade, double light,
                           double val) {
    auto rainbow = cyl_to_rgb | spectrum::filter_lightness(light) |
                   spectrum::filter_min_value(val);
    const auto color_name = colored_string::builder()
                                .data(name)
                                .foreground(grayscale_color{shade})
                                .build();
    println("{:~^10} rainbow ({}):", color_name, ranges::distance(rainbow));
    for (auto&& rgb : rainbow | views::values) {
      cout << display.set_background(rgb);
    }
    cout.put('\n');
  };

  show_rb("Dark", gray::G7, .3, .55);
  show_rb("Standard", gray::G15, .5, .95);
  show_rb("Pastel", gray::G23, .7, .95);
}
