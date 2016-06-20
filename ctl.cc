#include "ctl.h"
#include <iostream>
#include <map>
#include <algorithm>

using namespace CTL;

bool Formula::in(const std::vector<const Formula*> list) const
{
  return (std::find(list.begin(), list.end(), this) != list.end());
}

bool Formula::operator==(const Formula& o) const
{
  if (this->type != o.type)
  {
    return false;
  }
  switch (this->type)
  {
    case (Formula::_and):
    case (Formula::eu):
      return (((*this->psi) == (*(o.psi))) && ((*this->phi) == (*(o.phi))));
      break;
    case (Formula::_false):
      return true;
      break;
    case (Formula::_not):
    case (Formula::ex):
    case (Formula::af):
      return ((*this->phi) == (*(o.phi)));
      break;
    case (Formula::var):
      return (this->statement == o.statement);
      break;
  }
  return false;
}


bool Formula::evaluate(const State& init, const std::set<State>& states) const
{
  std::map<int, std::vector<const Formula*> > labels;
  Formula::generate_labels(states, labels);
  return this->in(labels[init.id]);
}

void Formula::generate_labels(const std::set<State>& states, std::map<int, std::vector<const Formula*> >& labels) const
{
  switch (this->type)
  {
    case (Formula::_false):
      break;
    case (Formula::var):
      for (const State& s : states)
      {
        if (s.statements.find(this->statement) != s.statements.end())
        {
          labels[s.id].push_back(this);
        }
      }
      break;
    case (Formula::_and):
      this->phi->generate_labels(states, labels);
      this->psi->generate_labels(states, labels);
      for (const State& s : states)
      {
        if (this->phi->in(labels[s.id]) && this->psi->in(labels[s.id]))
        {
          labels[s.id].push_back(this);
        }
      }
      break;
    case (Formula::_not):
      this->phi->generate_labels(states, labels);
      for (const State& s : states)
      {
        if (!this->phi->in(labels[s.id]))
        {
          labels[s.id].push_back(this);
        }
      }
      break;
    case (Formula::af):
      this->phi->generate_labels(states, labels);
      for (const State& s : states)
      {
        if (this->phi->in(labels[s.id]))
        {
          labels[s.id].push_back(this);
        }
      }
      {
        bool change = true;
        while (change)
        {
          change = false;
          for (const State& s : states)
          {
            if (this->in(labels[s.id]))
            {
              continue;
            }
            bool all_labeled_af = true;
            for (const State* succ_s : s.successors)
            {
              if (!this->in(labels[succ_s->id]))
              {
                all_labeled_af = false;
              }
            }
            if (all_labeled_af)
            {
              change = true;
              labels[s.id].push_back(this);
            }
          }
        }
      }
      break;
    case (Formula::eu):
      this->phi->generate_labels(states, labels);
      this->psi->generate_labels(states, labels);
      for (const State& s : states)
      {
        if (this->psi->in(labels[s.id]))
        {
          labels[s.id].push_back(this);
        }
      }
      {
        bool change = true;
        while (change)
        {
          change = false;
          for (const State& s : states)
          {
            if (!this->phi->in(labels[s.id]) || this->in(labels[s.id]))
            {
              continue;
            }
            bool one_labeled_eu = false;
            for (const State* succ_s : s.successors)
            {
              if (this->in(labels[succ_s->id]))
              {
                one_labeled_eu = true;
              }
            }
            if (one_labeled_eu)
            {
              change = true;
              labels[s.id].push_back(this);
            }
          }
        }
      }
      break;
    case (Formula::ex):
      this->phi->generate_labels(states, labels);
      for (const State& s : states)
      {
        for (const State* succ_s : s.successors)
        {
          if (this->phi->in(labels[succ_s->id]))
          {
            labels[s.id].push_back(this);
            break;
          }
        }
      }
      break;
  }
}
