#include "utility.hpp"
#include "Interval.hpp"
#include "Polynomial.hpp"
bool deq(double a, double b) { return std::abs(a - b) < EPSILON; }

bool ieq(Interval a, Interval b) {
  return deq(a.lower(), b.lower()) && deq(a.upper(), b.upper());
}

bool peq(Polynomial a, Polynomial b) {
  if (a.degree() != b.degree()) {
    return false;
  }
  for (size_t i = 0; i < a.degree(); i++) {
    if (!ieq(a.coef(i), b.coef(i))) {
      return false;
    }
  }
  return true;
}
