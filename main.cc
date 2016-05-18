#include <iostream>
#include "ctl.h"
#include "printalgebra.h"
#include "state.h"
#include "statement.h"

int main(void)
{
  // State s1 = State({Statement::A, Statement::B});
  CTL* p = AND(OR(TRUE, FALSE), FALSE);
  PrintAlgebra::evaluate(p);
  delete p;
  return 0;
}
