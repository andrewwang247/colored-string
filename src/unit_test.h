/*
Unit tests for cylindrical coordinates.

Copyright 2026. Andrew Wang.
*/
#pragma once

/**
 * Triplet of 3 equal types.
 */
template <typename T>
struct triplet {
 public:
  T m_a, m_b, m_c;

  triplet(T a, T b, T c);
};

namespace unit_test {
constexpr unsigned NUM_CASES = 5000;
constexpr double PRECISION = 1e-1;
/**
 * Run HSVL conversion tests against precomputed values.
 */
void hsvl();
}  // namespace unit_test

template <typename T>
triplet<T>::triplet(T a, T b, T c) : m_a(a), m_b(b), m_c(c) {}
