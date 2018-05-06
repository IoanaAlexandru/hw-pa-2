//
// Copyright Ioana Alexandru 2018
//

#ifndef TEMA2_PROBLEM_H
#define TEMA2_PROBLEM_H

#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <utility>
#include <vector>

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
  std::vector<int> minlexbfs;

 public:
  unsigned int N, M;
  // graph

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class Disjcnt : public Problem {
  std::vector<std::pair<int, int> > disjcnt;  // result is disjcnt.size()

 public:
  unsigned int N, M;
  // graph

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class RTD : public Problem {
  int rtd;

 public:
  unsigned int N, M, Sx, Sy, Fx, Fy, K;
  int cost[7];
  std::vector<std::vector<bool> > grid;  // false => blocked

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

class Revedges : public Problem {
  std::vector<int> revedges;

 public:
  unsigned int N, M, Q;
  // graph
  std::vector<std::pair<int, int> > query;

  bool Read(std::string filename) override;

  void Solve() override;

  bool Write(std::string filename) override;
};

}  // namespace tema2

#endif // TEMA2_PROBLEM_H
