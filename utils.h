//
// Copyright Ioana Alexandru 2018.
//

#ifndef TEMA2_UTILS_H
#define TEMA2_UTILS_H

#include <cstdint>
#include <set>
#include <utility>
#include <vector>

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

  Node &GetNode(int n);

  std::vector<Node> &GetNodes();

  void AddEdge(int n, int m);  // non-weighted graph

  void AddEdge(int n, int m, int w);
};

struct Cell {
  bool blocked;
  int cost;
  std::vector<std::pair<int, int> > path;

  explicit Cell(bool blocked) : blocked(blocked), cost(INT32_MAX) {};
};

enum direction { N, S, W, E };

struct Dice {
  int top, bottom, left, right, front, back;

  Dice() : top(6), bottom(1), left(4), right(3), front(5), back(2) {};

  Dice(int top, int bottom, int left, int right, int front, int back) :
      top(top),
      bottom(bottom),
      left(left),
      right(right),
      front(front),
      back(back) {};

  Dice Roll(enum direction d);
};

};  // namespace tema2

#endif //TEMA2_UTILS_H
