#include "builderunit.h"
#include "territory.h"
#include "action.h"

BuilderUnit::BuilderUnit(Territory * t, int nunit):  uTerritory(t), nUnits(nunit), uName("BuilderUnit")
{}

int BuilderUnit::increase (Unit* u)
{
   nUnits += u->numUnits();
   return nUnits;
}

int BuilderUnit::decrease (Unit* u)
{
   int tdec = u->numUnits();
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

int BuilderUnit::numUnits() const{
   return nUnits;
}

Territory* BuilderUnit::whereAt() const{
   return uTerritory;
}

std::string BuilderUnit::name() const{
   return uName;
}

std::vector<Action*> BuilderUnit::actions() const{}
