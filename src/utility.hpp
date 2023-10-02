#ifndef UTILITY_H_
#define UTILITY_H_

#include "Interval.hpp"
#include "Polynomial.hpp"

#define EPSILON 0.0001

bool deq(double a, double b);
bool ieq(const Interval &a, const Interval &b);
bool peq(const Polynomial &a, const Polynomial &b);

#endif // UTILITY_H_
