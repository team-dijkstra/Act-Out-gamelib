/*
Act-Out! game library - implements generic game logic.
Copyright (C) 2012 Rio Lowry, Chris Pinter, Matt Voroney

This file is part of Act-Out!

Act-Out! is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Act-Out! is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Act-Out!.  If not, see <http://www.gnu.org/licenses/>.
*/
/** \file landterritory.cc 
 * Implementation file for LandTerritory class
 * Detatailed descriptions of each method are in the header file
 */
#include "landterritory.h"
#include "player.h"
#include "unitoperation.h"
#include "unit.h"
#include "builderunit.h"

using namespace game;

/// \todo Change Player * own=NULL to unclaimed
LandTerritory::LandTerritory(std::string nm, Player* own):tName(nm), tOwner(own)
{
   Unit * tmp = new BuilderUnit(this,1);
   std::string s=tmp->name();
   tUnits[s]=tmp;
}

LandTerritory::~LandTerritory()
{
   /// \todo is this the correct behaviour for destructor?
   unitContainer::iterator it;
   for(it = tUnits.begin(); it != tUnits.end(); ++it)
      delete it->second;
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
/// \todo  use unitoperation to restrict units returned
LandTerritory::unitContainer LandTerritory::units(UnitOperation* f) const
{
   return tUnits;
}

void LandTerritory::owner(Player* p)
{
   tOwner = p;
}

void LandTerritory::addUnit(Unit * u)
{
   unitContainer::iterator it;
   std::string s=u->name();
   it=tUnits.find(s);
   if(it==tUnits.end())
      tUnits[u->name()]=u;
   else
      it->second->merge(u);
}
