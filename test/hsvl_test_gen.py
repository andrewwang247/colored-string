"""
Test case generator for RGB to HSV / HSL conversion.

Copyright 2026. Andrew Wang.
"""
from os import path
from pathlib import Path
from colorsys import rgb_to_hsv, rgb_to_hls
import numpy as np

# Required number of test cases
NUM_TESTS = 5_000
MAX_UCHAR = 2**8
FILE_DIR = Path(__file__).resolve().parent


@np.vectorize(signature='(3)->(3)')
def to_hsv(row: np.ndarray) -> np.ndarray:
    """Convert row from RGB to HSV."""
    h, s, v = rgb_to_hsv(*row)
    return np.array([360 * h, s, v])


@np.vectorize(signature='(3)->(3)')
def to_hsl(row: np.ndarray) -> np.ndarray:
    """Convert row from RGB to HSL."""
    h, l, s = rgb_to_hls(*row)
    return np.array([360 * h, s, l])


def main():
    """Generate test cases and export."""
    rgb_char = np.random.randint(0, MAX_UCHAR, (NUM_TESTS, 3))
    rgb_norm = rgb_char / MAX_UCHAR

    hsv = np.apply_along_axis(to_hsv, 1, rgb_norm)
    hsl = np.apply_along_axis(to_hsl, 1, rgb_norm)
    assert np.all(hsv[:, 0] == hsl[:, 0]), 'Hues for HSV/HSL should match.'

    np.savetxt(path.join(FILE_DIR, 'mat_rgb.txt'), rgb_char, r'%i')
    np.savetxt(path.join(FILE_DIR, 'mat_hsv.txt'), hsv, r'%.5f')
    np.savetxt(path.join(FILE_DIR, 'mat_hsl.txt'), hsl, r'%.5f')


if __name__ == '__main__':
    main()
