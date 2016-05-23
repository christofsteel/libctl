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
#include "statement.h"

// The following macros hide the allocation on the heap and calculate the
// TRANSLATE function, so every CTL formula can be represented by the operators
// FALSE, AND, AF, EU, EX and NOT.

#define FALSE new CTL(CTL::_false)
#define AND(x, y) new CTL(CTL::_and, x, y)
#define NOT(x) new CTL(CTL::_not, x)
#define VAR(x) new CTL(CTL::var, x)
#define EX(x) new CTL(CTL::ex, x)
#define EU(x, y) new CTL(CTL::eu, x, y)
#define AF(x) new CTL(CTL::af, x)

// TRANSLATE
#define TRUE NOT(FALSE)
#define EG(x) NOT(AF(NOT(x)))
#define EF(x) EU(TRUE, x)
#define AX(x) NOT(EX(NOT(x)))
#define OR(x, y) NOT(AND(NOT(x), NOT(y)))
#define AG(x) NOT(EU(TRUE, NOT(x)))
#define AU(x, y) AND(NOT(EU(NOT(y), AND(NOT(x), NOT(y)))), AF(y))


class CTL
{
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

    //     _or,
    //     _true,
    //     eg,
    //     ef,
    //     ax,
    //     ag,
    //     au
  };
  const CTL* phi;
  const CTL* psi;
  const Statement statement;
  const Type type;
  CTL(const Type type) : phi(0), psi(0), statement(NO_STATEMENT), type(type) {}
  CTL(const Type type, const CTL* iphi) : phi(iphi), psi(0), statement(NO_STATEMENT), type(type) {}
  CTL(const Type type, const Statement s) : phi(0), psi(0), statement(s), type(type) {}
  CTL(const Type type, const CTL* iphi, const CTL* ipsi) : phi(iphi), psi(ipsi), statement(NO_STATEMENT), type(type) {}
  void print() const;
  bool operator==(const CTL& o) const;
  bool operator<(const CTL& o) const;
  bool in(const std::vector<CTL> list) const;
};


/**
 * Definition of all CTL operators as a class to emulate the sum type CTL.
 * To seperate the types at runtime, we save a type inside the CTL object.
 */
/*
class And : public CTL
{
 public:
  const CTL* psi;
  const CTL* phi;
  And(const CTL* ipsi, const CTL* iphi) : psi(ipsi), phi(iphi), CTL(CTL::_and) {}
  ~And()
  {
    delete psi;
    delete phi;
  }
};


class _False : public CTL
{
 public:
  _False() : CTL(CTL::_false) {}
};


class Not : public CTL
{
 public:
  const CTL* phi;
  Not(const Not& p) : phi(p.phi), CTL(CTL::_not) {
  }
  Not(const CTL* iphi) : phi(iphi), CTL(CTL::_not) {}
  ~Not() { delete phi; }
};

class Var : public CTL
{
 public:
  const Statement statement;
  Var(const Statement& s) : statement(s), CTL(CTL::var) {}
};

class Ex : public CTL
{
 public:
  const CTL* phi;
  Ex(const CTL* iphi) : phi(iphi), CTL(CTL::ex) {}
  ~Ex() { delete phi; }
};


class Eu : public CTL
{
 public:
  const CTL* phi;
  const CTL* psi;
  Eu(const CTL* phi, const CTL* psi) : phi(phi), psi(psi), CTL(CTL::eu) {}
  ~Eu()
  {
    delete phi;
    delete psi;
  }
};


class Af : public CTL
{
 public:
  const CTL* phi;
  Af(const CTL* phi) : phi(phi), CTL(CTL::af) {}
  ~Af() { delete phi; }
};
*/
/*
// We define the missing connectives in case we need them later. Although I
// doubt it

class Or : public CTL {
  public:
  const CTL* psi;
  const CTL* phi;
  Or(const CTL* ipsi, const CTL* iphi) : psi(ipsi), phi(iphi), CTL(CTL::_or) {}
  ~Or() {
    delete psi;
    delete phi;
  }
};

class _True : public CTL {
  public:
  _True() : CTL(CTL::_true) {}
};

class Eg : public CTL {
  public:
  const CTL* phi;
  Eg(const CTL* iphi) : phi(iphi), CTL(CTL::eg) {}
  ~Eg() {
    delete phi;
  }
};

class Ef : public CTL {
  public:
  const CTL* phi;
  Ef(const CTL* phi) : phi(phi), CTL(CTL::ef) {}
  ~Ef() {
    delete phi;
  }
};

class Au : public CTL {
  public:
  const CTL* phi;
  const CTL* psi;
  Au(const CTL* phi, const CTL* psi) : phi(phi), psi(psi), CTL(CTL::au) {}
  ~Au() {
    delete phi;
    delete psi;
  }
};

class Ax : public CTL {
  public:
  const CTL* phi;
  Ax(const CTL* phi) : phi(phi), CTL(CTL::ax) {}
  ~Ax() {
    delete phi;
  }
};

class Ag : public CTL {
  public:
  const CTL* phi;
  Ag(const CTL* phi) : phi(phi), CTL(CTL::ag) {}
  ~Ag() {
    delete phi;
  }
};
*/
