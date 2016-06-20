#pragma once
#include <iostream>
#include <set>
#include "statement.h"

namespace CTL
{
class State
{
 private:
  static int max_id;

 public:
  int id;
  std::set<Statement> statements;
  std::set<State*> successors;
  State(std::set<Statement> statements) : id(max_id++), statements(statements){};
  inline void add_sibl(State* s) { this->successors.insert(s); }
  inline void add_statement(Statement s) { this->statements.insert(s); }
  inline bool operator<(const State& other) const { return this->id < other.id; }
};
}
