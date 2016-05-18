#pragma once
#include <iostream>
#include <set>
#include "ctl.h"
#include "statement.h"


class State
{
 private:
  static int max_id;

 public:
  int id;
  std::set<Statement> statements;
  std::set<State*> children;
  State(std::set<Statement> statements) : id(max_id++), statements(statements){};
  void add_sibl(State* s) { this->children.insert(s); }
  inline const bool operator<(const State& other) { return this->id < other.id; }
  void print() const
  {
    std::cout << this->id << ":";
    for (const State* s : this->children)
    {
      std::cout << " " << s->id;
    }
    std::cout << " |";
    for (const Statement& s : statements)
    {
      std::cout << " ";
    }
    std::cout << std::endl;
  }
  bool operator<(const State& o) const { return this->id < o.id; }
};
