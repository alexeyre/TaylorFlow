#include "Interval.hpp"
#include <algorithm>
#include <stdio.h>
using namespace std;
void Interval::print() { printf("[%f, %f]\n", m_lower_bound, m_upper_bound); }

Interval Interval::operator*(const Interval &other) {
  double a = m_lower_bound * other.m_lower_bound;
  double b = m_lower_bound * other.m_upper_bound;
  double c = m_upper_bound * other.m_lower_bound;
  double d = m_upper_bound * other.m_upper_bound;
  double lower_bound = min({a, b, c, d});
  double upper_bound = max({a, b, c, d});
  return Interval(lower_bound, upper_bound);
}

Interval Interval::operator*(const double scalar) {
  double new_lower_bound = scalar * m_lower_bound;
  double new_upper_bound = scalar * m_upper_bound;
  return Interval(new_lower_bound, new_upper_bound);
}

void Interval::operator*=(const double scalar) {
  m_lower_bound *= scalar;
  m_upper_bound *= scalar;
}

void Interval::operator*=(const Interval &other) {
  double a = m_lower_bound * other.m_lower_bound;
  double b = m_lower_bound * other.m_upper_bound;
  double c = m_upper_bound * other.m_lower_bound;
  double d = m_upper_bound * other.m_upper_bound;
  double lower_bound = min({a, b, c, d});
  double upper_bound = max({a, b, c, d});
  m_lower_bound = lower_bound;
  m_upper_bound = upper_bound;
}

void Interval::operator+=(const Interval &other) {
  m_lower_bound += other.m_lower_bound;
  m_upper_bound += other.m_upper_bound;
}

Interval Interval::extend(t_coef error) const {
  return Interval(m_lower_bound - error, m_upper_bound + error);
}
void Interval::extendInPlace(t_coef error) {
  m_lower_bound -= error;
  m_upper_bound += error;
}
