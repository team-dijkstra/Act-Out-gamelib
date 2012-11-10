#include "landterritory.h"
#include "player.h"
#include "filter.h"
#include "unit.h"
#include "builderunit.h"

/// \todo Change Player * own=NULL to unclaimed
LandTerritory::LandTerritory(std::string nm, Player* own = NULL):tName(nm), tOwner(own)
{
   Unit * tmp = new BuilderUnit(this,1);
   tUnits.push_back(tmp);
}

Player* LandTerritory::owner() const
{
   return tOwner;
}

std::string LandTerritory::name() const
{
   return tName;
}

/// \todo  build factoryunit in constructor...
/// \todo  use filter to restrict units returned
std::vector<Unit*> LandTerritory::units(Filter* f) const
{
   return tUnits;
}

void LandTerritory::owner(Player* p)
{
   tOwner = p;
}
