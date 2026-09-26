/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include "demo.h"

#include <iostream>
#include <print>

#include "colored_string.h"
#include "hsl_color.h"
#include "hsv_color.h"
#include "true_color.h"

using std::cout;
using std::print;
using std::println;

int main() {
  demo::paint_america();
  demo::display_rainbows();
}

void demo::paint_america() {
  const auto red = true_color{.red = 179, .green = 25, .blue = 66};
  const auto white = true_color{.red = 255, .green = 255, .blue = 255};
  const auto blue = true_color{.red = 10, .green = 49, .blue = 97};

  const auto white_star =
      colored_string{.data = "X", .foreground = white, .background = blue};
  const auto red_patch = colored_string{.background = red};
  const auto white_patch = colored_string{.background = white};
  const auto blue_patch = colored_string{.background = blue};

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
}

void demo::display_rainbows() {
  auto display = colored_string{.data = " "};

  const auto show_rb = [&display](const char* name, double light) {
    println("{:~^10} rainbow:", name);
    constexpr auto incr = 360 / WIDTH;
    for (auto i = 0U; i != WIDTH; ++i) {
      const auto hue = static_cast<double>(incr * i);
      const auto hsl = hsl_color{hue, .5, light};
      display.background = hsl.to_rgb();
      cout << display;
    }
    cout.put('\n');
  };

  show_rb("Dark", .25);
  show_rb("Standard", .5);
  show_rb("Pastel", .75);

  println("{:~^10} rainbow:", "Gray");
  constexpr auto incr = 1. / WIDTH;
  for (auto i = 0U; i != WIDTH; ++i) {
    const auto hsv = hsv_color{0., 0., incr * i};
    display.background = hsv.to_rgb();
    cout << display;
  }
  cout.put('\n');
}
