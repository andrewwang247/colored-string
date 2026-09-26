# Colored String

The `colored_string` class is an extension of `std::string` that adds 24-bit ANSI "true color" foregrounds and backgrounds when printing to the command line. Build and run `demo` or `unit_test` with the `Makefile` targets:

- `run` / `release` option to run / build a demo of colored strings
- `test` / `debug` option to run / build unit testing suite

Check that your terminal support 24-bit colors by running

```bash
echo $COLORTERM
```

If it shows `truecolor` or `24bit`, you are good to go!

## Colors

Each 24-bit ANSI color uses 8 bits for each of the red, green, and blue channels. This yields a total of $256 = 2^8$ values per channel, yielding $16777216 = 256^3$ possible colors. More information about ANSI color codes can be found on [Wikipedia](https://en.wikipedia.org/wiki/ANSI_escape_code). In code, `std::uint8_t` is used to represent channel values.

Colors do not come into play until a `colored_string` is printed, either via `operator<<` or `std::print` and its ilk. If a foreground or background color is defined, escape sequences are added such that a color (*r*, *g*, *b*) in base-10 numerics will have the sequence `\x1b[<e>;2;<r>;<g>;<b>m` inserted into the stream before the body of the string.

Substitute `<e>` with `38` for foreground colors and `48` for background colors. This operation assumes that the ANSI symbols for begin and end escape sequences are `\x1b` and `m` respectively, which is often the case. After the body of the string, the sequence `\x1b[0m` is added to reset foreground and background back to their default states.

This is the main advantage of encapsulating the color state into a `colored_string` class. Colors have a user-defined lifetime and scope. The user is free to print strings with any foreground and background combination. The color state of the stream always returns to default. Without this encapsulation, the user must keep track of state after every print.

## HSV / HSL

As a showcase of what you can do with colored strings, we include an implementation of [HSV and HSL](https://en.wikipedia.org/wiki/HSL_and_HSV) that is interoperable with our `true_color` type. The HSV / HSL spaces are much better at mapping to human spectral perception than RGB as shown in `demo`. Test cases for conversion between sRGB and HSV/L are stored in the CSV files under `resources`.
