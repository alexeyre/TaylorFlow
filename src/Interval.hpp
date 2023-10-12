#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "Types.h"
#include <cmath>
#include <limits>
#include <string>
#include <utility>

using namespace std;
class Interval {
public:
  Interval(double single_bound) {
    this->m_lower_bound = single_bound;
    this->m_upper_bound = single_bound;
  };
  explicit Interval(double lower_bound, double upper_bound)
      : m_lower_bound(lower_bound), m_upper_bound(upper_bound){};
  explicit Interval(pair<double, double> interval)
      : m_lower_bound(interval.first), m_upper_bound(interval.second){};
  explicit Interval();

  Interval operator+(const Interval &other) const {
    return Interval(m_lower_bound + other.m_lower_bound,
                    m_upper_bound + other.m_upper_bound);
  };
  Interval operator-(const Interval &other) const {
    return Interval(m_lower_bound - other.m_lower_bound,
                    m_upper_bound - other.m_upper_bound);
  }

  Interval operator*(const Interval &other) const;
  Interval operator*(const double scalar) const;
  Interval operator/(const double scalar) const {
    return *this * 1.0 / scalar;
  };

  void operator*=(const double scalar);
  void operator*=(const Interval &other);
  void operator+=(const Interval &other);
  void operator-=(const Interval &other);

  Interval extend(t_coef error) const;
  void extendInPlace(t_coef error);

  const double lower() const { return m_lower_bound; }
  const double upper() const { return m_upper_bound; }

  Interval flip() const;

  static Interval pow(Interval interval, int i);

  void print() const;
  string str() const;

private:
  double m_lower_bound, m_upper_bound;
};

#endif // INTERVAL_H_
