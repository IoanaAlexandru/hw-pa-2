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
  for (auto q : query_) {  // Using Dijkstra
    int source = q.first, destination = q.second;
    g_.InitSource(source);
    std::priority_queue<std::pair<Node *, int>,
                        std::vector<std::pair<Node *, int> >, minWeight> queue;
    for (unsigned int i = 1; i <= N_; i++) {
      Node *u = &g_.GetNode(i);
      for (auto e : g_.GetNode(source).edges) {
        Node *v = e.first;
        int weight = e.second;
        if (u == v) {
          u->d = weight;
          queue.push(e);
        }
      }
    }

    while (!queue.empty()) {
      auto u = queue.top();
      queue.pop();
      u.first->col = grey;

      for (auto v : u.first->edges) {
        if (v.first->col == white && v.first->d > u.first->d + v.second) {
          v.first->d = u.first->d + v.second;
          queue.push(v);
        }
      }
    }

    revedges_.push_back(g_.GetNode(destination).d);
  }
}

bool tema2::Revedges::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  for (auto i : revedges_)
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
