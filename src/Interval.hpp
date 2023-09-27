#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "Types.h"
#include <cmath>
#include <limits>
class Interval {
public:
  Interval(double lower_bound, double upper_bound)
      : m_lower_bound(lower_bound), m_upper_bound(upper_bound){};

  Interval operator+(const Interval &other) {
    return Interval(m_lower_bound + other.m_lower_bound,
                    m_upper_bound + other.m_upper_bound);
  };

  Interval operator*(const Interval &other);
  Interval operator*(const double scalar);
  void operator*=(const double scalar);
  void operator*=(const Interval &other);
  void operator+=(const Interval &other);

  Interval extend(t_coef error) const;
  void extendInPlace(t_coef error);

  void print();

private:
  double m_lower_bound, m_upper_bound;
};

#endif // INTERVAL_H_
