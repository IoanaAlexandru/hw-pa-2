//
// Copyright Ioana Alexandru 2018
//

#ifndef TEMA2_PROBLEM_H
#define TEMA2_PROBLEM_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

namespace tema2 {

enum color { white, grey, black };

struct Node {
  int n;
  std::vector<std::pair<Node *, int> > edges;
  // if a node m is in edges, that means there is an edge n->m
  enum color col;
  int d;  // distance to source node

  explicit Node(int n) : n(n), edges(), col(white), d() {};
};

struct minWeight {
  bool operator()(const std::pair<Node *, int> &p1,
                  const std::pair<Node *, int> &p2) {
    return p1.second < p2.second;
  }
};

class Graph {
  bool oriented_;
  std::vector<Node> nodes_;

 public:
  Graph() : oriented_(false), nodes_() {};

  Graph(unsigned long N, bool oriented) : oriented_(oriented) {
    for (unsigned int i = 0; i <= N; i++)
      nodes_.emplace_back(i);
  };

  Node &GetNode(int n) { return nodes_[n]; }

  void AddEdge(int n, int m) {  // non-weighted graph
    nodes_[n].edges.emplace_back(&GetNode(m), 0);
    if (!oriented_)
      nodes_[m].edges.emplace_back(&GetNode(n), 0);
  }

  void AddEdge(int n, int m, int w) {
    nodes_[n].edges.emplace_back(&GetNode(m), w);
    if (!oriented_)
      nodes_[m].edges.emplace_back(&GetNode(n), w);
  }

  void SortEdges() {
    for (auto &n : nodes_)
      std::sort(n.edges.begin(), n.edges.end());
  }

  void InitSource(int source) {
    for (auto &n : nodes_) {
      if (n.n == source) {
        n.d = 0;
        n.col = grey;
      } else {
        n.d = INT32_MAX;
        n.col = white;
      }
    }
  }
};

class Problem {
 public:
  /*
   * Read data from file.
   */
  virtual bool Read(std::string filename) = 0;

  /*
   * Solve problem.
   */
  virtual void Solve() = 0;

  /*
   * Write solution to file.
   */
  virtual bool Write(std::string filename) = 0;
};

class Minlexbfs : public Problem {
  std::vector<int> minlexbfs_;

 public:
  unsigned int N_, M_;
  Graph g_;

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class Disjcnt : public Problem {
  std::vector<std::pair<int, int> > disjcnt_;  // result is disjcnt.size()

 public:
  unsigned int N_, M_;
  // graph

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class RTD : public Problem {
  int rtd_;

 public:
  unsigned int N_, M_, Sx_, Sy_, Fx_, Fy_, K_;
  int cost_[7];
  std::vector<std::vector<bool> > grid_;  // false => blocked

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class Revedges : public Problem {
  std::vector<int> revedges_;

 public:
  unsigned int N_, M_, Q_;
  Graph g_;
  std::vector<std::pair<int, int> > query_;

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

}  // namespace tema2

#endif // TEMA2_PROBLEM_H
