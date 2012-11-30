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
/** \file filterbyterritoryowner.cc
 * Implementation file for FilterByTerritoryOwner class
 * Detatailed descriptions of each method are in the header file
 */
#include "filterbyterritoryowner.h"
#include "player.h"
#include "territory.h"

FilterByTerritoryOwner::FilterByTerritoryOwner(const std::string & t):territoryOwner(t)
{
}

bool FilterByTerritoryOwner::operator()(Territory * t)
{
   return ( t->owner()->name() == territoryOwner);
}
