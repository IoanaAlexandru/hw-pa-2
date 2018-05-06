//
// Copyright Ioana Alexandru 2018
//

#include "./problem.h"

namespace tema2 {

bool tema2::Minlexbfs::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  minlexbfs.clear();

  f >> N >> M;

  // Read graph data TODO

  f.close();
  return true;
}

void tema2::Minlexbfs::Solve() {
  // TODO
}

bool tema2::Minlexbfs::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  for (auto i : minlexbfs)
    f << i << " ";

  f.close();
  return true;
}

}  // namespace tema2

int main() {
  tema2::Minlexbfs problem;

  if (!problem.Read("minlexbfs.in")) {
    std::cerr << "Could not open file minlexbfs.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("minlexbfs.out")) {
    std::cerr << "Could not open file minlexbfs.out" << std::endl;
    return -1;
  }

  return 0;
}
