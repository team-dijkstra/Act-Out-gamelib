#include "buildtraditionalarmyaction.h"
#include "phase.h"
#include "territory.h"
#include "traditionalarmy.h"

BuildTraditionalArmyAction::BuildTraditionalArmyAction(Phase* p):aName("BuildTraditionalArmy"), aPhase(p)
{}

std::string BuildTraditionalArmyAction::name() const
{
   return aName;
}

bool BuildTraditionalArmyAction::applicable(Phase* p) const
{
   if(p==aPhase)
      return true;
   return false;
}

void BuildTraditionalArmyAction::doaction(int nUnits, Territory* T)
{
   Unit* newArmy;
   newArmy = new TraditionalArmy(T, nUnits);
   /// \todo put this unit in territory's unit container??
   delete newArmy;//temporary fix
}
