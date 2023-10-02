#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include "Interval.hpp"
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Polynomial {
public:
  explicit Polynomial(){};
  explicit Polynomial(const vector<double> &coeffs);
  explicit Polynomial(const vector<Interval> &coeffs)
      : m_coefficients(std::move(coeffs)){};
  explicit Polynomial(const vector<pair<double, double>> &coeffs);

  Interval evaluate(double point);
  Interval evaluate(Interval interval);
  Interval evaluate(pair<double, double> interval);

  size_t degree() const { return m_coefficients.size(); }
  Interval coef(size_t i) const { return m_coefficients[i]; }

  void print() const;
  string sprint() const;

  Polynomial integrate(size_t n) const;
  Polynomial integrate() const { return integrate(1); }
  void integrate_inplace(size_t n);
  void integrate_inplace() { integrate_inplace(1); }

  void truncate_inplace(const size_t degree);
  Polynomial truncate(const size_t degree) const;

  Polynomial compose(const Polynomial &other) const;
  Polynomial pow(const int i) const;

  void operator+=(const Polynomial &other);
  void operator*=(const Polynomial &other);
  void operator*=(const Interval &scalar);
  void operator-=(const Polynomial &other);
  Polynomial operator+(const Polynomial &rhs) const {
    Polynomial result(*this);
    result += rhs;
    return result;
  }
  Polynomial operator*(const Polynomial &rhs) const;

  Polynomial picard(Polynomial g_i) const;

private:
  vector<Interval> m_coefficients;
};

#endif // POLYNOMIAL_H_
