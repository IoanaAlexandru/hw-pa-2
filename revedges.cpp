//
// Copyright Ioana Alexandru 2018
//

#include <queue>
#include "./problem.h"

namespace tema2 {

bool tema2::Revedges::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  query_.clear();
  revedges_.clear();

  f >> N_ >> M_ >> Q_;

  // Read graph data
  g_ = Graph(N_, true);
  for (unsigned int i = 0; i < M_; i++) {
    int X, Y;
    f >> X >> Y;
    g_.AddEdge(X, Y);
    g_.AddEdge(Y, X, 1);
  }

  for (unsigned int i = 0; i < Q_; i++) {
    int X, Y;
    f >> X >> Y;
    query_.emplace_back(X, Y);
  }

  f.close();
  return true;
}

void tema2::Revedges::Solve() {
  // Floyd-Warshall

  int d[kNMax + 1][kNMax + 1];

  for (auto i = 1; i <= N_; i++)
    for (auto j = 1; j <= N_; j++)
      d[i][j] = INT32_MAX / 2;

  for (auto u : g_.GetNodes()) {
    for (auto v : u.edges)
      d[u.n][v.first->n] = std::min(d[u.n][v.first->n], v.second);
  }

  for (auto k = 1; k <= N_; k++)
    for (auto i = 1; i <= N_; i++)
      for (auto j = 1; j <= N_; j++)
        d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

  for (auto q : query_) {
    if (q.first == q.second)
      revedges_.push_back(0);
    else
      revedges_.push_back(d[q.first][q.second]);
  }
}

bool tema2::Revedges::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  for (auto i : revedges_)
    f << i << std::endl;

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
