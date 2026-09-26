/*
Colorful string demo.

Copyright 2026. Andrew Wang.
*/
#include "demo.h"

#include <cstdlib>
#include <iostream>
#include <print>
#include <string_view>

#include "colored_string.h"
#include "hsl_color.h"
#include "hsv_color.h"
#include "true_color.h"

using std::cout;
using std::getenv;
using std::print;
using std::println;
using std::string_view;

int main() {
  if (const auto* terminal = getenv("COLORTERM")) {
    println("echo $COLORTERM = {}", terminal);
  }

  demo::paint_america();
  demo::hue_rainbow("Dark", .25);
  demo::hue_rainbow("Middle", .5);
  demo::hue_rainbow("Bright", .75);
  demo::value_palette("Gray", 0., 0.);
  demo::value_palette("Desert", 25., .7);
  demo::value_palette("Forest", 140., .6);
}

void demo::paint_america() {
  println("America:");

  constexpr auto red = true_color{.red = 179, .green = 25, .blue = 66};
  constexpr auto white = true_color{.red = 255, .green = 255, .blue = 255};
  constexpr auto blue = true_color{.red = 10, .green = 49, .blue = 97};

  const auto red_hex =
      colored_string{.data = red.hex(), .foreground = red, .background = ~red};
  const auto white_hex = colored_string{
      .data = white.hex(), .foreground = white, .background = ~white};
  const auto blue_hex = colored_string{
      .data = blue.hex(), .foreground = blue, .background = ~blue};
  println("  Hex:{:^11}|{:^11}|{:^11}", red_hex, white_hex, blue_hex);

  const auto white_star =
      colored_string{.data = "X", .foreground = white, .background = blue};
  const auto red_patch = colored_string{.background = red};
  const auto white_patch = colored_string{.background = white};
  const auto blue_patch = colored_string{.background = blue};

  const auto red_star_line = [&blue_patch, &white_star, &red_patch]() {
    for (auto i = 0; i < 8; ++i) print("{:1}{}", blue_patch, white_star);
    println("{:1}{:26}", blue_patch, red_patch);
  };
  const auto white_star_line = [&blue_patch, &white_star, &white_patch]() {
    print("{:2}", blue_patch);
    for (auto i = 0; i < 7; ++i) print("{}{:1}", white_star, blue_patch);
    println("{:1}{:26}", blue_patch, white_patch);
  };

  red_star_line();
  white_star_line();
  red_star_line();
  white_star_line();
  red_star_line();
  white_star_line();
  red_star_line();

  for (auto i = 0; i < 3; ++i) {
    println("{:43}", white_patch);
    println("{:43}", red_patch);
  }
}

void demo::hue_rainbow(string_view name, double light) {
  println("{:~^10} rainbow:", name);
  constexpr auto incr = 360 / WIDTH;
  auto display = colored_string{.data = " "};
  for (auto i = 0U; i != WIDTH; ++i) {
    const auto hue = static_cast<double>(incr * i);
    const auto hsl = hsl_color{hue, .5, light};
    display.background = hsl.to_rgb();
    cout << display;
  }
  cout.put('\n');
}

void demo::value_palette(string_view name, double hue, double sat) {
  println("{:~^10} palette:", name);
  constexpr auto incr = 1. / WIDTH;
  auto display = colored_string{.data = " "};
  for (auto i = 0U; i != WIDTH; ++i) {
    const auto hsv = hsv_color{hue, sat, incr * i};
    display.background = hsv.to_rgb();
    cout << display;
  }
  cout.put('\n');
}
