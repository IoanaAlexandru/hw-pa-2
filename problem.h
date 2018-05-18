//
// Copyright Ioana Alexandru 2018
//

#ifndef TEMA2_PROBLEM_H
#define TEMA2_PROBLEM_H

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "./utils.h"

namespace tema2 {

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
  unsigned long sol_;
  std::vector<int> idx, lowlink;
  std::deque<int> S;
  std::vector<bool> S_contains; // S_contains[u] = true if u is in S

 public:
  unsigned int N_, M_;
  std::vector<std::vector<int> > adj;

  void Tarjan(int v, int &index);

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class RTD : public Problem {
  int rtd_;

  void Move(Dice dice, int x, int y, int prev_cost);

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
