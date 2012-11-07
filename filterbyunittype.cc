#include "filterbyunittype.h"
#include "unit.h"

FilterByUnitType::FilterByUnitType(Unit * u):unitType(u),fName( u->name() )
{
}

bool FilterByUnitType::operator()(Unit * unit)
{
   return ( unit->name() == unitType->name() );
}

std::string FilterByUnitType::name()
{
   return fName;
}
