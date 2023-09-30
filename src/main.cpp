#include "Polynomial.hpp"
#include "TaylorModel.hpp"
#include <stdio.h>
#include <utility> // for std::pair
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  vector<pair<double, double>> coeffs = {{0.0, 0.0}, {0.0, 0.0}, {-3.0, 7.0}};
  pair<double, double> error = {-1.0, 1.0};
  Model model((Polynomial(coeffs)), (Interval(error)));

  return 0;
}
