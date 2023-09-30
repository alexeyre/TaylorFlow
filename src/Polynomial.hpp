#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include "Interval.hpp"
#include <cstddef>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Polynomial {
public:
  Polynomial(vector<double> coeffs);
  Polynomial(vector<Interval> coeffs) : m_coefficients(std::move(coeffs)){};
  Polynomial(vector<pair<double, double>> coeffs);

  Interval evaluate(double point);
  Interval evaluate(Interval interval);
  Interval evaluate(pair<double, double> interval);

  size_t degree() { return m_coefficients.size(); }
  Interval coef(size_t i) { return m_coefficients[i]; }

  void print();
  string sprint();

  Polynomial integrate(size_t n) const;
  Polynomial integrate() const { return integrate(1); }
  void integrate_inplace(size_t n);
  void integrate_inplace() { integrate_inplace(1); }

private:
  vector<Interval> m_coefficients;
};

#endif // POLYNOMIAL_H_
