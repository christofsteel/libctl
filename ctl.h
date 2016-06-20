/**
 * This is the Definition of CTL formulas. Algebrawise this would be the
 * Termalgebra T_{CTL}.
 *
 * The syntax of a CTL formula is given by the following signature:
 *
 * Let V be a set of Statements and 1 any single elemented set.
 * CTL(V) = { {ctl}, {V,1}, F }
 * F = {
 *       TRUE: 1 -> ctl,
 *       FALSE : 1 -> ctl,
 *       AND: ctl x ctl -> ctl,
 *       OR: ctl x ctl -> ctl,
 *       NOT: ctl -> ctl,
 *       VAR: V -> ctl,
 *       EX: ctl -> ctl,
 *       EF: ctl -> ctl,
 *       EG: ctl -> ctl,
 *       EU: ctl x ctl -> ctl,
 *       AX: ctl -> ctl,
 *       AF: ctl -> ctl,
 *       AG: ctl -> ctl,
 *       AU: ctl x ctl -> ctl
 *       }
 *
 * Example usage:
 *    // Given Statements A, B, Algebra alg and State s1
 *    CTL* phi = EX(EU(AND(TRUE,VAR(A)),VAR(B)));
 *    alg.evaluate(phi, s1);
 *    // NOTE: Since the formulas are allocated on the heap, you have to
 *    // `delete` them manually.
 *    delete phi;
 */

#pragma once
#include <vector>
#include <map>
#include <set>
#include "state.h"
#include "statement.h"

// The following macros hide the allocation on the heap and calculate the
// TRANSLATE function, so every CTL formula can be represented by the operators
// FALSE, AND, AF, EU, EX and NOT.

#define FALSE new CTL::Formula(CTL::Formula::_false)
#define AND(x, y) new CTL::Formula(CTL::Formula::_and, x, y)
#define NOT(x) new CTL::Formula(CTL::Formula::_not, x)
#define VAR(x) new CTL::Formula(CTL::Formula::var, x)
#define EX(x) new CTL::Formula(CTL::Formula::ex, x)
#define EU(x, y) new CTL::Formula(CTL::Formula::eu, x, y)
#define AF(x) new CTL::Formula(CTL::Formula::af, x)

// TRANSLATE
#define TRUE NOT(FALSE)
#define EG(x) NOT(AF(NOT(x)))
#define EF(x) EU(TRUE, x)
#define AX(x) NOT(EX(NOT(x)))
#define OR(x, y) NOT(AND(NOT(x), NOT(y)))
#define AG(x) NOT(EU(TRUE, NOT(x)))
#define AU(x, y) AND(NOT(EU(NOT(y), AND(NOT(x), NOT(y)))), AF(y))

namespace CTL {
class Formula
{
  private:
    void generate_labels(const std::set<State>& states, std::map<int, std::vector<const Formula*> >& labels) const;
 public:
  /**
   * Some types are commented out, because they are emulated by other types.
   * See "3.4.5 Adequate Sets of CTL connectives of "Logic in Computer
   * Science: Modelling and Reasoning about Systems"
   */
  enum Type
  {
    _false = 0,
    _not = 1,
    var = 2,
    ex = 3,
    af = 4,
    _and = 5,
    eu = 6,
  };
  const Formula* phi;
  const Formula* psi;
  const Statement statement;
  const Type type;
  Formula(const Type type) : phi(0), psi(0), statement(NO_STATEMENT), type(type) {}
  Formula(const Type type, const Formula* iphi) : phi(iphi), psi(0), statement(NO_STATEMENT), type(type) {}
  Formula(const Type type, const Statement s) : phi(0), psi(0), statement(s), type(type) {}
  Formula(const Type type, const Formula* iphi, const Formula* ipsi) : phi(iphi), psi(ipsi), statement(NO_STATEMENT), type(type) {}
  void print() const;
  bool evaluate(const State& init, const std::set<State>& states) const;
  bool operator==(const Formula& o) const;
  bool operator<(const Formula& o) const;
  bool in(const std::vector<const Formula*> list) const;
  ~Formula() {
    if(phi) {
      delete phi;
    }
    if(psi) {
      delete psi;
    }
  }
};
}
