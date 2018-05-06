//
// Copyright Ioana Alexandru 2018
//

#include "./problem.h"

namespace tema2 {

bool tema2::Revedges::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  query.clear();
  revedges.clear();

  f >> N >> M >> Q;

  // Read graph data TODO

  for (auto i = 0; i < Q; i++) {
    int X, Y;
    f >> X >> Y;
    query.emplace_back(X, Y);
  }

  f.close();
  return true;
}

void tema2::Revedges::Solve() {
  // TODO
}

bool tema2::Revedges::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  for (auto i : revedges)
    f << i << " ";

  f.close();
  return true;
}

}  // namespace tema2

int main() {
  tema2::Revedges problem;

  if (!problem.Read("revedges.in")) {
    std::cerr << "Could not open file revedges.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("revedges.out")) {
    std::cerr << "Could not open file revedges.out" << std::endl;
    return -1;
  }

  return 0;
}
