#include "Polynomial.hpp"
#include "Interval.hpp"
#include "utility.hpp"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
using namespace std;

Interval Polynomial::evaluate(double point) {
  Interval acc(0.0, 0.0);
  if (point >= 0) {
    for (size_t i = 0; i < m_coefficients.size(); i++) {
      acc += m_coefficients[i] * powl(point, i);
    }
  } else {
    for (size_t i = 0; i < m_coefficients.size(); i += 2) {
      acc += m_coefficients[i] * powl(point, i);
    }
    for (size_t i = 1; i < m_coefficients.size(); i += 2) {
      acc += m_coefficients[i].flip() * powl(point, i);
    }
  }
  return acc;
}

Interval Polynomial::evaluate(Interval interval) {
  Interval acc(0.0, 0.0);
  for (size_t i = 0; i < m_coefficients.size(); i++) {
    auto interval_to_power = Interval::pow(interval, i);
    const Interval term = m_coefficients[i] * interval_to_power;
    acc += term;
  }
  return acc;
}

Interval Polynomial::evaluate(pair<double, double> interval) {
  return evaluate(Interval(interval.first, interval.second));
}

Polynomial::Polynomial(const vector<double> &coeffs) {
  std::vector<Interval> intervals;
  transform(coeffs.cbegin(), coeffs.cend(), back_inserter(intervals),
            [](double c) { return Interval(c); });
  m_coefficients = std::move(intervals);
}

Polynomial::Polynomial(const vector<pair<double, double>> &coeffs) {
  std::vector<Interval> intervals;
  transform(coeffs.cbegin(), coeffs.cend(), back_inserter(intervals),
            [](pair<double, double> c) { return Interval(c.first, c.second); });
  m_coefficients = std::move(intervals);
}

void Polynomial::print() const { cout << sprint() << endl; }

string Polynomial::sprint() const {
  if (degree() == 0)
    return "";
  string result = m_coefficients[0].str();
  for (size_t i = 1; i < degree(); i++) {
    result += " + " + m_coefficients[i].str() + " x^" + to_string(i);
  }
  return result;
}

// integration
Polynomial Polynomial::integrate(size_t n) const {
  // integrate n times
  vector<Interval> terms(n + m_coefficients.size());
  for (size_t i = 0; i < m_coefficients.size(); i++) {
    terms[i + n] = m_coefficients[i] * (1.0 / (i + n));
  }
  Polynomial result(terms);
  return result;
}

void Polynomial::integrate_inplace(size_t n) {
  m_coefficients.insert(m_coefficients.begin(), n, Interval());
  for (size_t i = n; i < m_coefficients.size(); i++) {
    m_coefficients[i] *= (1.0) / i;
  }
}

Polynomial Polynomial::compose(const Polynomial &other) const {
  // putting the other polynomial inside the current polynomial
  Polynomial result;
  for (size_t i = 0; i < degree(); i++) {
    // take the substituting polynomial to the correct power
    Polynomial subst = other.pow(i);
    subst *= this->coef(i);
    result += subst;
  }
  return result;
}

Polynomial Polynomial::pow(const int i) const {
  if (i == 0) {
    return Polynomial({Interval(1)});
  }
  if (i == 1) {
    return *this;
  }
  return *this * pow(i - 1);
}

void Polynomial::operator*=(const Interval &scalar) {
  for (size_t i = 0; i < this->degree(); i++) {
    m_coefficients[i] *= scalar;
  }
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const {
  vector<Interval> product_coefs(this->degree() + rhs.degree() - 1,
                                 Interval(0));
  for (size_t i = 0; i < this->degree(); i++) {
    for (size_t j = 0; j < rhs.degree(); j++) {
      product_coefs[i + j] += this->coef(i) * rhs.coef(j);
    }
  }
  return Polynomial(product_coefs);
}

void Polynomial::operator+=(const Polynomial &other) {
  if (other.degree() > degree()) {
    m_coefficients.resize(other.degree());
  }
  for (size_t i = 0; i < other.degree(); i++) {
    m_coefficients[i] += other.coef(i);
  }
}
void Polynomial::operator-=(const Polynomial &other) {
  if (other.degree() > degree()) {
    m_coefficients.resize(other.degree());
  }
  for (size_t i = 0; i < other.degree(); i++) {
    m_coefficients[i] -= other.coef(i);
  }
}
void Polynomial::operator*=(const Polynomial &other) {
  vector<Interval> coefficients(degree() + other.degree() - 1);
  for (size_t i = 0; i < degree(); i++) {
    for (size_t j = 0; j < other.degree(); j++) {
      coefficients[i + j] += m_coefficients[i] * other.coef(j);
    }
  }
  m_coefficients = coefficients;
}

void Polynomial::truncate_inplace(const size_t degree) {
  m_coefficients.resize(degree + 1);
}
Polynomial Polynomial::truncate(const size_t degree) const {
  Polynomial result(*this);
  result.truncate_inplace(degree + 1);
  return result;
}
