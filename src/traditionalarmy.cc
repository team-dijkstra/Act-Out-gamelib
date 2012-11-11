#include "traditionalarmy.h"
#include "territory.h"
#include "action.h"

TraditionalArmy::TraditionalArmy(Territory * t, int nunit): nUnits(nunit), uTerritory(t), uName("TraditionalArmy")
{}

/// \todo implement increase units
int TraditionalArmy::increase (Unit* u){
   nUnits += u->numUnits();
   return nUnits;
}

/// \todo implement decrease units
int TraditionalArmy::decrease (Unit* u){
   int tdec = u->numUnits();
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

int TraditionalArmy::numUnits() const{
   return nUnits;
}

Territory* TraditionalArmy::whereAt() const{
   return uTerritory;
}

std::string TraditionalArmy::name() const{
   return uName;
}

std::vector<Action*> TraditionalArmy::actions() const{
   return uActions;
}
