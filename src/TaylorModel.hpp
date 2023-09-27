#ifndef TAYLORMODEL_H_
#define TAYLORMODEL_H_

#include "Interval.hpp"
#include "Polynomial.hpp"
#include <algorithm>
using namespace std;

class Model {

public:
  Model();
  Model(Polynomial &&polynomial, Interval &&interval)
      : m_polynomial(std::move(polynomial)), m_interval(std::move(interval)){};
  Model(Interval &&interval, Polynomial &&polynomial)
      : m_polynomial(std::move(polynomial)), m_interval(std::move(interval)){};

  Model operator+(const Model &other);
  void operator+=(const Model &other);
  Model operator*(const Model &other);
  void operator*=(const Model &other);
  Model operator*(const t_coef scalar);
  void operator*=(const t_coef scalar);
  void print();

  Model lower(const size_t order);

private:
  Polynomial m_polynomial;
  Interval m_interval;
};

#endif // TAYLORMODEL_H_
