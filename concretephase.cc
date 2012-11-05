#include "concretephase.h"

using namespace std;

ConcretePhase::ConcretePhase (string nm): name(nm) {}

string ConcretePhase::name() const
{
   return name;
}
