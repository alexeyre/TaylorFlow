#include "Polynomial.hpp"
#include "Types.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>
using namespace std;

void Polynomial::print() {

  if (m_coefficients.empty()) {
    return;
  }
  if (m_coefficients.size() >= 1) {
    printf("%g", m_coefficients[0]);
  }
  if (m_coefficients.size() >= 2) {
    if (m_coefficients[1] == 1.0) {
      printf(" + x");
    } else {
      printf(" + %g * x", m_coefficients[1]);
    }
  }
  for (size_t index = 2; index < m_coefficients.size(); ++index) {
    if (m_coefficients[index] == 1.0) {
      printf(" + x^%lu", index);
    } else {
      printf(" + %g * x^%lu", m_coefficients[index], index);
    }
  }
  printf("\n");
}

double Polynomial::evaluate(double point) {
  double accumulator = 0.0;
  size_t index = 0;
  for (auto coef : m_coefficients) {
    accumulator += coef * powl(point, index);
    index++;
  }
  return accumulator;
}

Polynomial Polynomial::operator+(const Polynomial &rhs) {
  // assume lhs and rhs are same size
  t_vcoef new_coefficients(m_coefficients.size());
  for (size_t i = 0; i < m_coefficients.size(); i++) {
    new_coefficients[i] = m_coefficients[i] + rhs.m_coefficients[i];
  }
  Polynomial p(std::move(new_coefficients));
  return p;
}

Polynomial Polynomial::operator*(const Polynomial &other) {
  t_vcoef coefficients(m_coefficients.size() + other.m_coefficients.size() - 1);
  for (size_t i = 0; i < m_coefficients.size(); i++) {
    for (size_t j = 0; j < other.m_coefficients.size(); j++) {
      coefficients[i + j] += m_coefficients[i] * other.m_coefficients[j];
    }
  }
  return Polynomial(std::move(coefficients));
}

void Polynomial::operator*=(const Polynomial &other) {
  m_coefficients.reserve(m_coefficients.size() + other.m_coefficients.size() -
                         1);
  for (size_t i = 0; i < m_coefficients.size(); i++) {
    for (size_t j = 0; j < other.m_coefficients.size(); j++) {
      m_coefficients[i + j] += m_coefficients[i] * other.m_coefficients[j];
    }
  }
}

Polynomial Polynomial::operator*(const t_coef scalar) {
  t_vcoef coefficients(m_coefficients.size());
  for (size_t i = 0; i < m_coefficients.size(); i++) {
    coefficients[i] = m_coefficients[i] * scalar;
  }
  return Polynomial(std::move(coefficients));
}
void Polynomial::operator*=(const t_coef scalar) {
  for (size_t i = 0; i < m_coefficients.size(); i++) {
    m_coefficients[i] *= scalar;
  }
}

void Polynomial::operator+=(const Polynomial &other) {
  // assert(degree() == other.degree());
  for (size_t i = 0; i < degree(); i++) {
    m_coefficients[i] += other.m_coefficients[i];
  }
}

Polynomial Polynomial::lower(const size_t order) {
  if (order >= m_coefficients.size()) {
    return *this;
  }
  t_vcoef coefficients(order + 1);
  copy(m_coefficients.begin(), m_coefficients.begin() + order + 1,
       coefficients.begin());
  return Polynomial(std::move(coefficients));
}

bool Polynomial::lowerInPlace(const size_t order) {
  if (order >= m_coefficients.size()) {
    return false;
  }
  m_coefficients.resize(order + 1);
  return true;
}
