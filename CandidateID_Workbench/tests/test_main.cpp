#include "workbench.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
int main() {
  wb::ThermalConfig c; c.elements=10;
  auto r=wb::solve_thermal(c);
  assert(r.nodes.size()==11);
  assert(std::abs(r.nodes.front().temperature-100.0)<1e-10);
  assert(std::abs(r.nodes.back().temperature-20.0)<1e-10);
  auto n=wb::train_one_neuron(100);
  assert(n.finite_difference_max_error<1e-5);
  assert(n.loss_history.size()==101);
  std::cout<<"Core tests passed.\n";
}
