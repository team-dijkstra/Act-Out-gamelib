#include "fakeunit.h"
#include "action.h"

using namespace std;

//FakeUnit::FakeUnit(int nunit, Territory * t,  vector<Action*> uActs):nUnits(nunit), tWhere(t), uActions(uActs)
FakeUnit::FakeUnit(int nunit, Territory * t):nUnits(nunit), tWhere(t)
{
   uName = "FakeUnit";   
}

int FakeUnit:: increase (Unit* u)
{
   nUnits += u->numUnits();
   return nUnits;
}

int FakeUnit::decrease (Unit* u)
{
   int tdec = u->numUnits();
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

int FakeUnit::numUnits() const
{
   return nUnits;
}

Territory* FakeUnit::whereAt() const
{
   return tWhere;
}

std::string FakeUnit::name() const
{
   return uName;
}

std::vector<Action*> FakeUnit::actions() const
{
   return uActions;
}

