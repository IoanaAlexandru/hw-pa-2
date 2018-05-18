//
// Copyright Ioana Alexandru 2018
//

#include <fstream>
#include <iostream>
#include "./problem.h"
#include "./utils.h"

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

  for (unsigned int i = 0; i <= N_; i++) {
    std::vector<Cell> new_vec;
    grid_.push_back(new_vec);
    for (unsigned int j = 0; j <= M_; j++)
      grid_[i].emplace_back(false);
  }

  for (unsigned int i = 0; i < K_; i++) {
    int X, Y;
    f >> X >> Y;
    grid_[X][Y].blocked = true;
  }

  f.close();
  return true;
}

void tema2::RTD::Move(Dice dice, int x, int y, int prev_cost) {
  int move_cost = cost_[dice.bottom];
  if (prev_cost + move_cost <= grid_[x][y].cost)
    grid_[x][y].cost = prev_cost + move_cost;
  else
    return;

  if (prev_cost + cost_[dice.bottom] > grid_[Fx_][Fy_].cost)
    return;

  if (x == Fx_ && y == Fy_)
    return;

  if (x > 1 && !grid_[x - 1][y].blocked)
    Move(dice.Roll(N), x - 1, y, grid_[x][y].cost);
  if (x < N_ && !grid_[x + 1][y].blocked)
    Move(dice.Roll(S), x + 1, y, grid_[x][y].cost);
  if (y > 1 && !grid_[x][y - 1].blocked)
    Move(dice.Roll(W), x, y - 1, grid_[x][y].cost);
  if (y < M_ && !grid_[x][y + 1].blocked)
    Move(dice.Roll(E), x, y + 1, grid_[x][y].cost);
}

void tema2::RTD::Solve() {
  Dice dice(6, 1, 4, 3, 5, 2);

  Move(dice, Sx_, Sy_, 0);

  for (auto i = 1; i <= N_; i++) {
    for (auto j = 1; j <= M_; j++)
      std::cout << grid_[i][j].cost << ' ';
    std::cout << std::endl;
  }
  std::cout << std::endl;

  rtd_ = grid_[Fx_][Fy_].cost;
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
