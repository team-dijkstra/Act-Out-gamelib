#include "concretephase.h"

using namespace std;

ConcretePhase::ConcretePhase (const string & nm): phasename(nm) {}

string ConcretePhase::name() const
{
   return phasename;
}
