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
  rtd_ = 0;

  f >> N_ >> M_ >> Sx_ >> Sy_ >> Fx_ >> Fy_ >> K_;

  cost_[0] = -1;  // virtual element
  for (auto i = 1; i <= 6; i++)
    f >> cost_[i];

  for (unsigned int i = 0; i < N_; i++)
    for (unsigned int j = 0; j < M_; j++)
      grid_[i][j] = true;

  for (unsigned int i = 0; i < K_; i++) {
    int X, Y;
    f >> X >> Y;
    grid_[X][Y] = false;
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

  f << rtd_;

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
