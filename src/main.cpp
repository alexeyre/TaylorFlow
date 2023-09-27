#include "Interval.hpp"
#include "Polynomial.hpp"
#include "TaylorModel.hpp"
#include "Types.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  t_vcoef coefficients_1 = {1.0, 1.0, 1.0};
  auto p1 = Polynomial(std::move(coefficients_1));
  t_vcoef coefficients_2 = {2.0, 3.0, 4.0};
  auto p2 = Polynomial(std::move(coefficients_2));

  auto i1 = Interval(-INFINITY, 0.0);
  auto i2 = Interval(3.0, 7.0);

  auto m1 = Model(std::move(p1), std::move(i1));
  printf("M_1: ");
  m1.print();
  auto m2 = Model(std::move(p2), std::move(i2));
  printf("M_2: ");
  m2.print();
  auto m3 = m1 + m2;
  printf("M_1 + M_2: ");
  m3.print();
  auto m4 = m1 * m2;
  printf("M_1 * M_2: ");
  m4.print();

  auto m5 = (m1 * 2.0) + (m2 * 3.0);
  printf("2*M_1 + 3*M_2: ");
  m5.print();
  return 0;
}
