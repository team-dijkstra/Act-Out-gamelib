#include "filterbyallunittypes.h"
#include "unit.h"

FilterByAllUnitTypes::FilterByAllUnitTypes( Unit * u ) : unitType(u)
{
   fName = "AllUnits";
}

bool FilterByAllUnitTypes::operator()(Unit * unit)
{
   return true;
}

std::string FilterByAllUnitTypes::name()
{
   return fName;
}

