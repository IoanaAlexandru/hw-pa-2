//
// Copyright Ioana Alexandru 2018
//

#include <queue>
#include "./problem.h"

namespace tema2 {

bool tema2::Minlexbfs::Read(std::string filename) {
  std::ifstream f(filename);
  if (!f.is_open())
    return false;

  // Reset problem data
  minlexbfs_.clear();

  f >> N_ >> M_;

  // Read graph data
  g_ = Graph(N_, false);
  for (auto i = 0; i < M_; i++) {
    int X, Y;
    f >> X >> Y;
    g_.AddEdge(X, Y);
  }

  f.close();
  return true;
}

void tema2::Minlexbfs::Solve() {
  std::queue<Node*> q;
  Node *source = &g_.GetNode(1);  // Choosing lowest value node as source
  source->col = grey;
  q.push(source);

  while (!q.empty()) {
    Node* u = q.front();
    q.pop();
    minlexbfs_.push_back(u->n);

    for (auto v : u->edges) {
      if (v.first->col == white) {
        v.first->col = grey;
        q.push(v.first);
      }
    }

    u->col = black;
  }
}

bool tema2::Minlexbfs::Write(std::string filename) {
  std::ofstream f(filename);
  if (!f.is_open())
    return false;

  for (auto i : minlexbfs_)
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
