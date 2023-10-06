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

  Model picard(const Polynomial &p_F, const Interval x_0) const;

  void print() const {
    printf("Polynomial: ");

    m_polynomial.print();
    printf("\nerror: ");
    m_error.print();
    printf("\n");
  };

private:
  Polynomial m_polynomial;
  Interval m_error;
};

#endif // TAYLORMODEL_H_
