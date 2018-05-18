//
// Copyright Ioana Alexandru 2018.
//

#include "./utils.h"

bool tema2::EdgeComparator::operator()(const std::pair<Node *, int> &p1,
                                const std::pair<Node *, int> &p2) {
  if (p1.second == p2.second)
    return p1.first->n < p2.first->n;
  return p1.second < p2.second;
}

tema2::Node &tema2::Graph::GetNode(int n) { return nodes_[n]; }

std::vector<tema2::Node> &tema2::Graph::GetNodes() { return nodes_; }

void tema2::Graph::AddEdge(int n, int m) {  // non-weighted graph
  edges_.emplace_back(n, m);

  nodes_[n].edges.emplace(&GetNode(m), 0);
  if (!oriented_)
    nodes_[m].edges.emplace(&GetNode(n), 0);
}

void tema2::Graph::AddEdge(int n, int m, int w) {
  nodes_[n].edges.emplace(&GetNode(m), w);
  if (!oriented_)
    nodes_[m].edges.emplace(&GetNode(n), w);
}

tema2::Dice tema2::Dice::Roll(enum direction d) {
    Dice new_dice;

    if (d == E) {
      new_dice.top = left;
      new_dice.bottom = right;
      new_dice.left = bottom;
      new_dice.right = top;
      new_dice.front = front;
      new_dice.back = back;
    } else if (d == S) {
      new_dice.top = back;
      new_dice.bottom = front;
      new_dice.left = left;
      new_dice.right = right;
      new_dice.front = top;
      new_dice.back = bottom;
    } else if (d == W) {
      new_dice.top = right;
      new_dice.bottom = left;
      new_dice.left = top;
      new_dice.right = bottom;
      new_dice.front = front;
      new_dice.back = back;
    } else if (d == N) {
      new_dice.top = front;
      new_dice.bottom = back;
      new_dice.left = left;
      new_dice.right = right;
      new_dice.front = bottom;
      new_dice.back = top;
    }

    return new_dice;
}
