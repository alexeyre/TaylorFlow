#include "Polynomial.hpp"
#include "Interval.hpp"
#include <cstdio>
#include <iostream>
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

Polynomial::Polynomial(vector<double> coeffs) {
  std::vector<Interval> intervals;
  for (double coef : coeffs) {
    intervals.push_back(Interval(coef, coef));
  }
  m_coefficients = std::move(intervals);
}

Polynomial::Polynomial(vector<pair<double, double>> coeffs) {
  std::vector<Interval> intervals;
  for (pair<double, double> coef : coeffs) {
    intervals.push_back(Interval(coef.first, coef.second));
  }
  m_coefficients = std::move(intervals);
}

void Polynomial::print() { cout << sprint() << endl; }

string Polynomial::sprint() {
  size_t degree = m_coefficients.size();
  if (degree == 0)
    return "";
  string result = m_coefficients[0].str();
  for (size_t i = 1; i < degree; i++) {
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
