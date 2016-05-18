/**
 * This algebra prints out the formula. It is mainly for debugging purpuses.
 * only works on a reduced (adequate) subset of CTL connectives.
 *
 * The static method `evaluate` corresponds to the unique homomorphism fold
 * from the initial (term-)algebra T_{CTL} (See ctl.h) to this algebra.
 *
 * Example usage:
 *    // Given CTL Formulapointer phi.
 *    PrintAlgebra::evaluate(phi);
 */

#pragma once
#include <iostream>
#include "ctl.h"
#include "statement.h"

class PrintAlgebra
{
 public:
  static bool evaluate(const CTL* phi)
  {
    switch (phi->type)
    {
      case (CTL::_and):
      {
        const And* self = static_cast<const And*>(phi);
        std::cout << "(";
        PrintAlgebra::evaluate(self->phi);
        std::cout << " && ";
        PrintAlgebra::evaluate(self->psi);
        std::cout << ")";
      }
      break;
      case (CTL::_false):
      {
        std::cout << "0";
      }
      break;
      case (CTL::_not):
      {
        const Not* self = static_cast<const Not*>(phi);
        std::cout << "!(";
        PrintAlgebra::evaluate(self->phi);
        std::cout << ")";
      }
      break;
      case (CTL::var):
      {
        const Var* self = static_cast<const Var*>(phi);
        std::cout << "VAR(";
        switch (self->statement)
        {
          case (Statement::A):
            std::cout << "A";
            break;
          case (Statement::B):
            std::cout << "B";
            break;
          case (Statement::C):
            std::cout << "C";
            break;
          default:
            std::cout << self->statement;
            break;
        }
        std::cout << ")";
      }
      break;
      case (CTL::ex):
      {
        const Ex* self = static_cast<const Ex*>(phi);
        std::cout << "EX(";
        PrintAlgebra::evaluate(self->phi);
        std::cout << ")";
      }
      break;
      case (CTL::eu):
      {
        const Eu* self = static_cast<const Eu*>(phi);
        std::cout << "E[";
        PrintAlgebra::evaluate(self->phi);
        std::cout << " U ";
        PrintAlgebra::evaluate(self->psi);
        std::cout << "]";
      }
      break;
      case (CTL::af):
      {
        const Af* self = static_cast<const Af*>(phi);
        std::cout << "AF(";
        PrintAlgebra::evaluate(self->phi);
        std::cout << ")";
      }
      break;

        /*      case (CTL::_or):
              {
                const Or* self = static_cast<const Or*>(phi);
                std::cout << "(";
                PrintAlgebra::evaluate(self->phi);
                std::cout << " || ";
                PrintAlgebra::evaluate(self->psi);
                std::cout << ")";
              }
              break;
              case (CTL::_true):
              {
                std::cout << "1";
              }
              break;
              case (CTL::ax):
              {
                const Ax* self = static_cast<const Ax*>(phi);
                std::cout << "AX(";
                PrintAlgebra::evaluate(self->phi);
                std::cout << ")";
              }
              break;
              case (CTL::eg):
              {
                const Eg* self = static_cast<const Eg*>(phi);
                std::cout << "EG(";
                PrintAlgebra::evaluate(self->phi);
                std::cout << ")";
              }
              break;
              case (CTL::ef):
              {
                const Ef* self = static_cast<const Ef*>(phi);
                std::cout << "EF(";
                PrintAlgebra::evaluate(self->phi);
                std::cout << ")";
              }
              break;
              case (CTL::ag):
              {
                const Ag* self = static_cast<const Ag*>(phi);
                std::cout << "AG(";
                PrintAlgebra::evaluate(self->phi);
                std::cout << ")";
              }
              break;
              case (CTL::au):
              {
                const Au* self = static_cast<const Au*>(phi);
                std::cout << "A[";
                PrintAlgebra::evaluate(self->phi);
                std::cout << " U ";
                PrintAlgebra::evaluate(self->psi);
                std::cout << "]";
              }
              break; */
    }
    return true;
  }
};
