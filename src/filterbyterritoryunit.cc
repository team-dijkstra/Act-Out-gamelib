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
/** \file filterbyterritoryunit.cc
 * Implementation file for FilterByTerritoryUnit class
 * Detatailed descriptions of each method are in the header file
 */
#include "filterbyterritoryunit.h"
#include "filterbyallunittypes.h"
#include "player.h"
#include "territory.h"

FilterByTerritoryUnit::FilterByTerritoryUnit(const std::string & t):territoryUnit(t)
{
}

bool FilterByTerritoryUnit::operator()(Territory * t)
{
   Territory::unitContainer::iterator it;
   UnitOperation * f;
   f = new FilterByAllUnitTypes();
   for(it = t->units(f).begin(); it != t->units(f).end(); ++it)
      if(it->second->name() == territoryUnit)
      {
	 delete f;
	 return true;
      }
   delete f;
   return false;
}
