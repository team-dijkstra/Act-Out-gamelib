#include "landterritory.h"
#include "player.h"
#include "filter.h"
#include "unit.h"

/// \todo Change Player * own=NULL to unclaimed
LandTerritory::LandTerritory(std::string nm, Player* own = NULL):tName(nm), tOwner(own)
{}

Player* LandTerritory::owner() const
{}

std::string LandTerritory::name() const
{}

std::vector<Unit*> LandTerritory::units(Filter* f) const
{}

void LandTerritory::owner(Player*)
{}
