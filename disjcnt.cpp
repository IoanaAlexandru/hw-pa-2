//
// Copyright Ioana Alexandru 2018
//

#include "./problem.h"

namespace tema2 {

bool tema2::Disjcnt::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  disjcnt_.clear();

  f >> N_ >> M_;

  // Read graph data TODO

  f.close();
  return true;
}

void tema2::Disjcnt::Solve() {
  // TODO
}

bool tema2::Disjcnt::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  f << disjcnt_.size();

  f.close();
  return true;
}

}  // namespace tema2

int main() {
  tema2::Disjcnt problem;

  if (!problem.Read("disjcnt.in")) {
    std::cerr << "Could not open file disjcnt.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("disjcnt.out")) {
    std::cerr << "Could not open file disjcnt.out" << std::endl;
    return -1;
  }

  return 0;
}
