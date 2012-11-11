#ifndef BUILD_TRADITIONAL_ARMY_ACTION_H
#define BUILD_TRADITIONAL_ARMY_ACTION_H

#include "action.h"

class BuildTraditionalArmyAction : public Action{
  public:
   BuildTraditionalArmyAction(Phase* p);
   ~BuildTraditionalArmyAction(){}

   //accessors
   std::string name() const;
   bool applicable(Phase* p) const;

   //mutators
   void doaction(int nUnits, Territory* T);

  private:

   std::string aName;
   Phase* aPhase;
};

#endif
