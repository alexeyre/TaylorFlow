#ifndef TAYLORMODEL_H_
#define TAYLORMODEL_H_

#include "Interval.hpp"
#include "Polynomial.hpp"
#include <algorithm>
using namespace std;

class Model {
public:
  Model(Polynomial polynomial, Interval error)
      : m_polynomial(std::move(polynomial)), m_error(std::move(error)){};

private:
  Polynomial m_polynomial;
  Interval m_error;
};

#endif // TAYLORMODEL_H_
