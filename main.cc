#include <iostream>
#include <set>
#include "ctl.h"
#include "evalalgebra.h"
#include "printalgebra.h"
#include "state.h"
#include "statement.h"

int main(void)
{
  State s1 = State({Statement::A});
  State s2 = State({Statement::A});
  State s3 = State({Statement::A});
  State s4 = State({Statement::B});
  State s5 = State({Statement::B});

  s1.add_sibl(&s2);
  s2.add_sibl(&s1);
  s3.add_sibl(&s1);
  s3.add_sibl(&s2);
  s3.add_sibl(&s4);
  s3.add_sibl(&s5);
  s4.add_sibl(&s5);
  s5.add_sibl(&s4);

  std::set<State> states {s1, s2, s3, s4, s5};

  CTL* p = AG(VAR(A)); //AU(NOT(TRUE), FALSE); //AND(OR(TRUE, FALSE), TRUE);
  CTL* q = AND(OR(TRUE, FALSE), FALSE);
  PrintAlgebra::evaluate(p);
  std::cout << std::endl;
  bool eval = EvalAlgebra::evaluate(*p, s1, states);
//  std::cout << std::endl << ((*p) == (*q)) << std::endl;
  std::cout << eval << std::endl;
  delete p;
  delete q;
  return 0;
}
