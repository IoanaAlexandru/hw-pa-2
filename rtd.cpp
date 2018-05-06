//
// Copyright Ioana Alexandru 2018
//

#include "./problem.h"

namespace tema2 {

bool tema2::RTD::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  rtd = 0;

  f >> N >> M >> Sx >> Sy >> Fx >> Fy >> K;

  cost[0] = -1;  // virtual element
  for (auto i = 1; i <= 6; i++)
    f >> cost[i];

  for (auto i = 0; i < N; i++)
    for (auto j = 0; j < M; j++)
      grid[i][j] = true;

  for (auto i = 0; i < K; i++) {
    int X, Y;
    f >> X >> Y;
    grid[X][Y] = false;
  }

  f.close();
  return true;
}

void tema2::RTD::Solve() {
  // TODO
}

bool tema2::RTD::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  f << rtd;

  f.close();
  return true;
}

}  // namespace tema2

int main() {
  tema2::RTD problem;

  if (!problem.Read("rtd.in")) {
    std::cerr << "Could not open file rtd.in" << std::endl;
    return -1;
  }

  problem.Solve();

  if (!problem.Write("rtd.out")) {
    std::cerr << "Could not open file rtd.out" << std::endl;
    return -1;
  }

  return 0;
}
