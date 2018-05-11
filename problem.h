//
// Copyright Ioana Alexandru 2018
//

#ifndef TEMA2_PROBLEM_H
#define TEMA2_PROBLEM_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

namespace tema2 {

const int kNMax{500};

enum color { white, grey, black };

struct Node;

struct EdgeComparator {
  bool operator()(const std::pair<Node *, int> &p1,
                  const std::pair<Node *, int> &p2);
};

struct Node {
  int n;
  std::multiset<std::pair<Node *, int>, EdgeComparator> edges;
  enum color col;

  explicit Node(int n) : n(n), edges(), col(white) {};
};

bool EdgeComparator::operator()(const std::pair<Node *, int> &p1,
                                const std::pair<Node *, int> &p2) {
  if (p1.second == p2.second)
    return p1.first->n < p2.first->n;
  return p1.second < p2.second;
}

class Graph {
  bool oriented_;
  std::vector<Node> nodes_;
  std::vector<std::pair<int, int> > edges_;

 public:
  Graph() : oriented_(false), nodes_() {};

  Graph(unsigned long N, bool oriented) : oriented_(oriented) {
    for (unsigned int i = 0; i <= N; i++)
      nodes_.emplace_back(i);
  };

  Node &GetNode(int n) { return nodes_[n]; }

  std::vector<Node> &GetNodes() { return nodes_; }

  void AddEdge(int n, int m) {  // non-weighted graph
    edges_.emplace_back(n, m);

    nodes_[n].edges.emplace(&GetNode(m), 0);
    if (!oriented_)
      nodes_[m].edges.emplace(&GetNode(n), 0);
  }

  void AddEdge(int n, int m, int w) {
    nodes_[n].edges.emplace(&GetNode(m), w);
    if (!oriented_)
      nodes_[m].edges.emplace(&GetNode(n), w);
  }

//  void SortEdges() {
//    for (auto &n : nodes_)
//      std::sort(n.edges.begin(), n.edges.end());
//  }
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

struct Cell {
  bool blocked;
  int cost;

  Cell(bool blocked) : blocked(blocked), cost(INT32_MAX) {};
};

class RTD : public Problem {
  int rtd_;

  void move(int pos, int x, int y, int cost, int prev_x, int prev_y);

 public:
  unsigned int N_, M_, Sx_, Sy_, Fx_, Fy_, K_;
  int cost_[7];
  std::vector<std::vector<Cell> > grid_;  // false => blocked

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
