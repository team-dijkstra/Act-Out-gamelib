#include "fakeunit.h"
#include "action.h"

using namespace std;

FakeUnit::FakeUnit(int nunit, Territory * t,  vector<Action*> uActs):nUnits(nunit), tWhere(t), uActions(uActs){
   uName = "FakeUnit";
   
}

int FakeUnit:: increase (Unit* u){}

int FakeUnit::decrease (Unit* u){}

int FakeUnit::numUnits() const{}

Territory* FakeUnit::whereAt() const{}

std::string FakeUnit::name() const{}

std::vector<Action*> FakeUnit::actions() const{}

