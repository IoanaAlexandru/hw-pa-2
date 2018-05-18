//
// Copyright Ioana Alexandru 2018
//

#include <algorithm>
#include "./utils.h"
#include "./problem.h"

namespace tema2 {

bool tema2::Disjcnt::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  f >> N_ >> M_;
  sol_ = 0;
  lowlink.reserve(N_ + 1);
  for (auto v = 0; v <= N_; v++) {
    S_contains.push_back(false);
    idx.push_back(-1);
  }
  S.clear();

  // Read graph data TODO
  adj.reserve(N_ + 1);
  for (unsigned int i = 0; i < M_; i++) {
    int X, Y;
    f >> X >> Y;
    adj[X].push_back(Y);
    adj[Y].push_back(X);
  }

  f.close();
  return true;
}

void tema2::Disjcnt::Tarjan(int v, int &index) {
  idx[v] = index;
  lowlink[v] = index;
  index++;
  S.push_back(v);
  S_contains[v] = true;

  for (auto u : adj[v]) {
      // Removing reverse edge
      auto reverse = std::find(adj[u].begin(), adj[u].end(), v);
      if (reverse != adj[u].end())
        adj[u].erase(reverse);

      if (idx[u] == -1) {
        Tarjan(u, index);
        lowlink[v] = std::min(lowlink[v], lowlink[u]);
      } else if (S_contains[u]) {
        lowlink[v] = std::min(lowlink[v], idx[u]);
      }
  }

  unsigned long CTC_size = 0;
  if (lowlink[v] == idx[v]) {
    int u = 0;
    while (u != v && !S.empty()) {
      u = S.back();
      S.pop_back();
      S_contains[u] = false;
      CTC_size++;
    }

    sol_ += CTC_size * (CTC_size - 1) / 2;
  }
}

void tema2::Disjcnt::Solve() {
  std::vector<std::vector<int>> sol;
  int index = 0;
  Tarjan(1, index);
}

bool tema2::Disjcnt::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  f << sol_;

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
