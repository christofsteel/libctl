#include <chrono>
#include <iostream>
#include <set>
#include <string>
#include "ctl.h"
#include "state.h"
#include "statement.h"


std::set<CTL::State>* createModel(int size)
{
  std::set<CTL::State>* states = new std::set<CTL::State>;
  for (int i = 0; i < size; i++)
  {
    CTL::State s({Statement::A, Statement::B, Statement::C});
    states->insert(s);
  }
  for (auto i : *states)
  {
    for (auto j : *states)
    {
      i.add_sibl(&j);
    }
  }
  return states;
}

int main(int argc, char* argv[])
{
  int size = 0;
  if(argc < 2) {
    std::cout << "Nope" << std::endl;
    exit(0);
  }
  size = std::stoi(argv[1]);
  std::set<CTL::State>* states = createModel(size);

  CTL::Formula* p = AG(AND(VAR(A), AG(AX(VAR(B)))));//AG(VAR(A));  // AU(NOT(TRUE), FALSE); //AND(OR(TRUE, FALSE), TRUE);
//  CTL* p = AG(AND(AG(AX(VAR(B))), VAR(A)));//AND(VAR(A), AG(AX(B)));//AG(VAR(A));  // AU(NOT(TRUE), FALSE); //AND(OR(TRUE, FALSE), TRUE);
  //  CTL* q = AND(OR(TRUE, FALSE), FALSE);
  auto start_time = std::chrono::high_resolution_clock::now();
  bool eval = p->evaluate(*(states->begin()), *states);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto time = end_time - start_time;
  std::cout << size << 
    ", " <<  std::chrono::duration_cast<std::chrono::microseconds>(time).count() << std::endl;

//  delete p;
  return 0;
}
