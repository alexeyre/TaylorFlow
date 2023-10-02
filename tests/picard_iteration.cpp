#include "../src/Polynomial.hpp"
#include "../src/utility.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

Polynomial picard_iteration(const Polynomial &p_F, const Interval &x_0, int n,
                            int max_iterations = 4) {
  vector<Polynomial> g;
  Polynomial g_0({x_0});
  g.push_back(g_0);
  for (int i = 1; i < max_iterations; i++) {
    Polynomial subst = p_F.compose(g[i - 1]);
    subst.integrate_inplace();
    subst.truncate_inplace(n);
    subst -= Polynomial({subst.evaluate(0.0)});
    g.push_back(subst);
    // convergence
    if (peq(g[i], g[i - 1]))
      break;
  }
  return g.back();
}

TEST_CASE("Test picard iteration for TMFC paper example", "[picard]") {
  Polynomial p_F(vector<double>{1.0, 0.0, 1.0});
  Polynomial p_F_picard = picard_iteration(p_F, Interval(0), 3);
  Polynomial p_F_picard_expected(
      Polynomial(vector<Interval>{0, 1, 0, 1.0 / 3.0}));
  REQUIRE(peq(p_F_picard_expected, p_F_picard));
}
