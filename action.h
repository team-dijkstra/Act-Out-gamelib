#ifndef ACTION_H
#define ACTION_H

#include <string>

class Territory;
class Phase;

class Action {
  public:
   virtual ~Action() {}

   //accessors
   virtual std::string name() const =0;
   virtual bool applicable(Phase* p) const =0;

   //mutators
   virtual void do(int nUnits,Territory* T) =0;
    
};

#endif
