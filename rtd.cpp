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

  for (unsigned int i = 0; i < N_; i++) {
    std::vector<Cell> new_vec;
    grid_.push_back(new_vec);
    for (unsigned int j = 0; j < M_; j++)
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

// pos -> dice side facing down

enum move { up, down, left, right };

int GetPos(enum move mov, int pos) {
  switch (pos) {
    case 1:
      switch (mov) {
        case up: return 2;
        case down: return 5;
        case left: return 4;
        case right: return 3;
      }
    case 2:
      switch (mov) {
        case up: return 6;
        case down: return 1;
        case left: return 4;
        case right: return 3;
      }
    case 3:
      switch (mov) {
        case up: return 2;
        case down: return 5;
        case left: return 1;
        case right: return 6;
      }
    case 4:
      switch (mov) {
        case up: return 5;
        case down: return 2;
        case left: return 1;
        case right: return 6;
      }
    case 5:
      switch (mov) {
        case up: return 3;
        case down: return 4;
        case left: return 1;
        case right: return 6;
      }
    case 6:
      switch (mov) {
        case up: return 3;
        case down: return 4;
        case left: return 5;
        case right: return 2;
      }
    default:return 0;
  }
}

void tema2::RTD::move(int pos, int x, int y, int cost, int prev_x, int prev_y) {
  if (prev_x == -1 && prev_y == -1)
    grid_[x][y].cost = cost;
  else if (grid_[prev_x][prev_y].cost + cost < grid_[x][y].cost)
    grid_[x][y].cost = grid_[prev_x][prev_y].cost + cost;
  else
    return;

  // up
  if (x > 0 && !grid_[x - 1][y].blocked)
    move(GetPos(up, pos), x - 1, y, cost_[pos], x, y);
  // down
  if (x < N_ - 1 && !grid_[x + 1][y].blocked)
    move(GetPos(down, pos), x + 1, y, cost_[pos], x, y);
  // left
  if (y > 0 && !grid_[x][y - 1].blocked)
    move(GetPos(left, pos), x, y - 1, cost_[pos], x, y);
  // right
  if (y < M_ - 1 && !grid_[x][y + 1].blocked)
    move(GetPos(right, pos), x, y + 1, cost_[pos], x, y);
}

void tema2::RTD::Solve() {
  move(1, Sx_, Sy_, 0, -1, -1);

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
