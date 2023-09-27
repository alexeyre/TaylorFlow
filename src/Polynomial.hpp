#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include "Types.h"
#include <vector>
using namespace std;

class Polynomial {
public:
  Polynomial();

  Polynomial(vector<t_coef> &&coefficients)
      : m_coefficients(std::move(coefficients)){};

  void print();

  double evaluate(double point);

  Polynomial operator+(const Polynomial &other);
  void operator+=(const Polynomial &other);
  Polynomial operator*(const Polynomial &other);
  void operator*=(const Polynomial &other);

  // creates a new polynomial multiplied by the scalar
  Polynomial operator*(const t_coef scalar);
  void operator*=(const t_coef scalar);

  Polynomial lower(const size_t order);
  bool lowerInPlace(const size_t order);

  t_coef coef(const size_t order) { return m_coefficients[order]; }
  size_t degree() const { return m_coefficients.size(); }

private:
  vector<t_coef> m_coefficients;
};

#endif // POLYNOMIAL_H_
