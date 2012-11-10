#include "builderunit.h"
#include "territory.h"
#include "action.h"

BuilderUnit::BuilderUnit(Territory * t, int nunit=1):  uTerritory(t), nUnits(nunit), uName("BuilderUnit")
{}

int BuilderUnit::increase (Unit* u)
{
   return numUnits();
}

int BuilderUnit::decrease (Unit* u)
{
   return numUnits();
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
