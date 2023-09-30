#include "../src/Polynomial.hpp"
#include "../src/utility.hpp"
#include <catch2/catch_test_macros.hpp>
#include <utility>

TEST_CASE("Test point-polynomial evaluation at point", "[polynomial]") {
  Polynomial p({1.0, 2.0, 3.0});
  Interval result = p.evaluate(2.0);
  REQUIRE(result.lower() == result.upper());
  REQUIRE(deq(result.lower(), 17.0));
}

TEST_CASE("Test point-polynomial evaluation on interval", "[polynomial]") {}

TEST_CASE("Test interval-polynomial evaluation at point", "[polynomial]") {
  vector<pair<double, double>> coefs = {{-1.0, 2.0}, {0.0, 3.0}, {6.0, 10.0}};
  Polynomial p(coefs);
  Interval result = p.evaluate(2.0);
  REQUIRE(deq(result.lower(), 23.0));
  REQUIRE(deq(result.upper(), 48.0));

  result = p.evaluate(-3.0);
  REQUIRE(deq(result.lower(), 44.0));
  REQUIRE(deq(result.upper(), 92.0));
}

TEST_CASE("Test interval-polynomial evaluation on interval", "[polynomial]") {
  vector<pair<double, double>> coefs = {{-1.0, 2.0}, {0.0, 3.0}, {6.0, 10.0}};
  Polynomial p(coefs);
  Interval result = p.evaluate(make_pair(-2.0, 3.0));
  REQUIRE(deq(result.lower(), -67.0));
  REQUIRE(deq(result.upper(), 101.0));

  result = p.evaluate(make_pair(-37.0, 410.0));
  REQUIRE(deq(result.lower(), -151812.0));
  REQUIRE(deq(result.upper(), 1682232.0));
}

// TEST_CASE("Test polynomial printing", "[polynomial]") {
//   Polynomial p({{-1.0, 2.0}, {0.0, 3.0}, {6.0, 10.0}});
//   REQUIRE(p.sprint() == "[-1.000000, 2.000000] + [0.000000, 3.000000] x^1 + "
//                         "[6.000000, 10.000000] x^2");

//   Polynomial empty_p;
//   REQUIRE(empty_p.sprint() == "");

//   Polynomial singleton_p({{-1.0, 7.0}});
//   REQUIRE(singleton_p.sprint() == "[-1.00000, 7.00000]");
// }

TEST_CASE("Test polynomial once-integration inplace", "[polynomial]") {
  vector<pair<double, double>> p_coefs = {
      {-1.0, -1.0}, {7.0, 7.0}, {10.0, 10.0}};
  vector<pair<double, double>> p_int_coefs = {
      {0.0, 0.0}, {-1.0, -1.0}, {3.5, 3.5}, {3.333333, 3.333333}};

  Polynomial p(p_coefs);
  p.integrate_inplace();
  REQUIRE(peq(p, Polynomial(p_int_coefs)));
}

TEST_CASE("Test polynomial twice-integration inplace", "[polynomial]") {
  vector<pair<double, double>> p_coefs = {
      {-1.0, -1.0}, {7.0, 7.0}, {10.0, 10.0}};
  vector<pair<double, double>> p_tint_coefs = {
      {0.0, 0.0}, {0.0, 0.0}, {-0.5, -0.5}, {2.333333, 2.333333}, {2.5, 2.5}};

  Polynomial p(p_coefs);
  p.integrate_inplace(2);
  REQUIRE(peq(p, Polynomial(p_tint_coefs)));
}

TEST_CASE("Test polynomial once-integretion", "[polynomial]") {
  vector<pair<double, double>> p_coefs = {
      {-1.0, -1.0}, {7.0, 7.0}, {10.0, 10.0}};
  vector<pair<double, double>> p_int_coefs = {
      {0.0, 0.0}, {-1.0, -1.0}, {3.5, 3.5}, {3.333333, 3.333333}};
  Polynomial p_int = Polynomial(p_coefs).integrate();
  REQUIRE(peq(p_int, Polynomial(p_int_coefs)));
}

TEST_CASE("Test polynomial twice-integretion", "[polynomial]") {
  vector<pair<double, double>> p_coefs = {
      {-1.0, -1.0}, {7.0, 7.0}, {10.0, 10.0}};
  vector<pair<double, double>> p_tint_coefs = {
      {0.0, 0.0}, {0.0, 0.0}, {-0.5, -0.5}, {2.333333, 2.333333}, {2.5, 2.5}};

  Polynomial p_int = Polynomial(p_coefs).integrate(2);
  REQUIRE(peq(p_int, Polynomial(p_tint_coefs)));
}
