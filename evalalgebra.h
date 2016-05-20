#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "ctl.h"
#include "printalgebra.h"
#include "state.h"

class EvalAlgebra
{
 public:
  /*
  bool evaluate(const CTL& phi, const State& init)
  {
    std::map< const State&, std::set<const CTL&>& > labels;
    evaluate_(phi, init, labels);
    std::cout << "Labels: " << std::endl;
    for(const State& s: this->states) {
      std::cout << "State: " << s.id << " ";
      for(const CTL& label: labels[s]) {

      }
    }
    return labels[init].find(phi) != labels[init].end();
  }
  */
  static bool evaluate(const CTL& phi, const State& init, const std::set<State>& states)
  {
    std::map<int, std::vector<CTL> > labels;
    EvalAlgebra::evaluate_(phi, states, labels);
    std::cout << "List of labels" << std::endl;
    for (const State& s : states)
    {
      std::cout << "Labels for State " << s.id << std::endl;
      for (const CTL& phi : labels[s.id])
      {
        PrintAlgebra::evaluate(&phi);
        std::cout << std::endl;
      }
    }
    return phi.in(labels[init.id]);
  }

  static void evaluate_(const CTL& phi, const std::set<State>& states, std::map<int, std::vector<CTL> >& labels)
  {
    switch (phi.type)
    {
      case (CTL::_false):
        break;
      case (CTL::var):
        for (const State& s : states)
        {
          if (s.statements.find(phi.statement) != s.statements.end())
          {
            labels[s.id].push_back(phi);
          }
        }
        break;
      case (CTL::_and):
        EvalAlgebra::evaluate_(*phi.phi, states, labels);
        EvalAlgebra::evaluate_(*phi.psi, states, labels);
        for (const State& s : states)
        {
          if (phi.phi->in(labels[s.id]) && phi.psi->in(labels[s.id]))
          {
            labels[s.id].push_back(phi);
          }
        }
        break;
      case (CTL::_not):
        EvalAlgebra::evaluate_(*phi.phi, states, labels);
        for (const State& s : states)
        {
          if (!phi.phi->in(labels[s.id]))
          {
            labels[s.id].push_back(phi);
          }
        }
        break;
      case (CTL::af):
        EvalAlgebra::evaluate_(*phi.phi, states, labels);
        for (const State& s : states)
        {
          if (phi.phi->in(labels[s.id]))
          {
            labels[s.id].push_back(phi);
          }
        }
        {
          bool change = true;
          while (change)
          {
            change = false;
            for (const State& s : states)
            {
              bool all_labeled_af = true;
              for (const State* succ_s : s.successors)
              {
                if (!phi.in(labels[succ_s->id]))
                {
                  all_labeled_af = false;
                }
              }
              if (all_labeled_af)
              {
                change = true;
                labels[s.id].push_back(phi);
              }
            }
          }
        }
        break;
      case (CTL::eu):
        EvalAlgebra::evaluate_(*phi.phi, states, labels);
        EvalAlgebra::evaluate_(*phi.psi, states, labels);
        for(const State& s: states) {
          if(phi.psi->in(labels[s.id])) {
            labels[s.id].push_back(phi);
          }
        }
        {
          bool change = true;
          while (change)
          {
            change = false;
            for (const State& s : states)
            {
              if(!phi.phi->in(labels[s.id])) {
                continue;
              }
              bool one_labeled_eu = false;
              for (const State* succ_s : s.successors)
              {
                if (phi.in(labels[succ_s->id]))
                {
                  one_labeled_eu = true;
                }
              }
              if (one_labeled_eu)
              {
                change = true;
                labels[s.id].push_back(phi);
              }
            }
          }
        }
        break;
      case (CTL::ex):
        EvalAlgebra::evaluate_(*phi.phi, states, labels);
        for(const State& s: states) {
          for(const State* succ_s: s.successors) {
            if(phi.phi->in(labels[succ_s->id])) {
              labels[s.id].push_back(phi);
              break;
            }
          }
        }
        break;
    }
  }
};
