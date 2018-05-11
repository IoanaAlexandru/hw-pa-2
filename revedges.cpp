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
  std::vector<std::vector<int> > cache(kNMax);

  for (auto q : query_) {  // Using Dijkstra
    int source = q.first, destination = q.second;

    if (!cache[source].empty()) {
      revedges_.push_back(cache[source][destination]);
      continue;
    }

    std::vector<int> d(kNMax);
    std::queue<std::pair<Node *, int> > queue;

    for (auto i = 1; i <= N_; i++) {
      d[i] = INT32_MAX;
      g_.GetNode(i).col = white;
    }
    d[source] = 0;
    g_.GetNode(source).col = grey;
    for (auto u : g_.GetNode(source).edges) {
      if (u.second < d[u.first->n])
        d[u.first->n] = u.second;
      queue.push(u);
    }

    while (!queue.empty()) {
      auto u = queue.front();
      queue.pop();
      u.first->col = grey;

      for (auto v : u.first->edges) {
        if (v.first->col == white && d[v.first->n] > d[u.first->n] + v.second) {
          d[v.first->n] = d[u.first->n] + v.second;
          queue.push(v);
        }
      }
    }

    cache[source] = d;

    revedges_.push_back(cache[source][destination]);
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
