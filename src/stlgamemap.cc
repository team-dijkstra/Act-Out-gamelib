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

#include "territory.h"
#include "stlgamemap.h"

StlGameMap::StlGameMap(const AdjacencyList & tal) {
    /// \todo build graph.
}

StlGameMap::~StlGameMap() {}

Territory* StlGameMap::find(TerritoryName) const {
   return NULL; 
}


GameMap::TerritoryList StlGameMap::adjacencies(Territory *) const {
   return TerritoryList();
}


GameMap::TerritoryList StlGameMap::players(Player *) const {
   return TerritoryList(); 
}


void StlGameMap::traverse(TerritoryOperation * op, Territory * start) {
   //foo
}


GameMap::TerritoryList StlGameMap::filter(TerritoryOperation * op) const {
   return TerritoryList(); 
}

