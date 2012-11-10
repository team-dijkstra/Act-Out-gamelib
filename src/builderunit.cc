#include "builderunit.h"
#include "territory.h"
#include "action.h"

BuilderUnit::BuilderUnit(int nunit, Territory * t): nUnits(nunit), uTerritory(t), uName("BuilderUnit")
{}

int BuilderUnit::increase (Unit* u){}

int BuilderUnit::decrease (Unit* u){}

int BuilderUnit::numUnits() const{}

Territory* BuilderUnit::whereAt() const{}

std::string BuilderUnit::name() const{}

std::vector<Action*> BuilderUnit::actions() const{}
