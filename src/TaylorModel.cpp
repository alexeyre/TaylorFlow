#include "TaylorModel.hpp"

Model Model::operator+(const Model &other) {
  auto new_interval = m_interval + other.m_interval;
  auto new_polynomial = m_polynomial + other.m_polynomial;
  return Model(std::move(new_polynomial), std::move(new_interval));
}

void Model::print() {
  m_interval.print();
  m_polynomial.print();
  printf("\n");
}

Model Model::operator*(const Model &other) {
  auto new_interval = m_interval * other.m_interval;
  auto new_polynomial = m_polynomial * other.m_polynomial;
  return Model(std::move(new_polynomial), std::move(new_interval));
}

Model Model::operator*(const t_coef scalar) {
  auto new_interval = m_interval * scalar;
  auto new_polynomial = m_polynomial * scalar;
  return Model(std::move(new_polynomial), std::move(new_interval));
}

void Model::operator+=(const Model &other) {
  m_polynomial += other.m_polynomial;
  m_interval += other.m_interval;
}

void Model::operator*=(const Model &other) {
  m_polynomial *= other.m_polynomial;
  m_interval *= other.m_interval;
}

void Model::operator*=(const t_coef scalar) {
  m_polynomial *= scalar;
  m_interval *= scalar;
}

Model Model::lower(const size_t order) {
  Polynomial lower_polynomial = m_polynomial.lower(order);
  t_coef totalErr = 0;
  for (size_t i = order + 1; i < m_polynomial.degree(); i++) {
    totalErr += abs(m_polynomial.coef(i));
  }
  Interval new_interval = m_interval.extend(totalErr);
  return Model(std::move(lower_polynomial), std::move(new_interval));
}
