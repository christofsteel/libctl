#include "ctl.h"
#include <iostream>
#include "printalgebra.h"

bool CTL::in(const std::vector<CTL> list) const
{
  std::cout << "Searching for ";
  PrintAlgebra::evaluate(this);
  std::cout << std::endl;
  for (const auto& phi : list)
  {
    if (*this == phi)
    {
      return true;
    }
  }
  return false;
}

bool CTL::operator==(const CTL& o) const
{
  if (this->type != o.type)
  {
    return false;
  }
  switch (this->type)
  {
    case (CTL::_and):
    case (CTL::eu):
      return (((*this->psi) == (*(o.psi))) && ((*this->phi) == (*(o.phi))));
      break;
    case (CTL::_false):
      return true;
      break;
    case (CTL::_not):
    case (CTL::ex):
    case (CTL::af):
      return ((*this->phi) == (*(o.phi)));
      break;
    case (CTL::var):
      return (this->statement == o.statement);
      break;
  }
}
