#include "../src/Interval.hpp"
#include "../src/utility.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Test interval multiplication", "[interval]") {
  Interval i1(make_pair(-7.0, 33.0));
  Interval i2(make_pair(14.0, 107.0));
  Interval i3(make_pair(-749.0, 3531.0));

  REQUIRE(ieq(i1 * i2, i3));
  i1 *= i2;
  REQUIRE(ieq(i1, i3));
}

TEST_CASE("Test interval addition", "[interval]") {
  Interval i1(make_pair(-7.0, 33.0));
  Interval i2(make_pair(14.0, 107.0));
  Interval i3(make_pair(7.0, 140.0));

  REQUIRE(ieq(i1 + i2, i3));
  i1 += i2;
  REQUIRE(ieq(i1, i3));
}
