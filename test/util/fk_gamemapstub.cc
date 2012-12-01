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
/// \file fk_gamemapstub.h
/// \brief Interface file for GameMap Class 
//
/// Fake class implements GameMap interface.
#include <vector>
#include <utility>
#include <string>

#include "fk_gamemapstub.h"
#include "defaultplayer.h"
#include "landterritory.h"
#include "defaultphase.h"

//class Player;
//class Territory;
//class TerritoryOperation;

FakeGameMap::FakeGameMap(TerritoryList tl, AdjacencyList al): tList(tl),aList(al)
{
   t1 = new LandTerritory(std::string("Spain"));
}
			     
FakeGameMap::~FakeGameMap() {
   delete t1;
}
  
//accessors
/// \return the start territory. Which territory this is is implementation
///       defined.
Territory* FakeGameMap::begin() const{
   TerritoryList::const_iterator it;
   it = tList.begin();
   return (*it);
//   return t1;   
}
   
/// Finds the specified Territory
//
/// \param tname -- string representing the TerritoryName
/// \return the specified Territory, or a sentinel if not found.
/// \see StlGameMap::end the sentinel node of this class.
Territory* FakeGameMap::find(TerritoryName fn) const{
   TerritoryList::const_iterator it;
   it = tList.begin();
   for ( ; it != tList.end(); ++it)
   {
      std::string n = (*it)->name();
      if (n == fn)
	 return (*it);
   }
   return (*it);
}

/// Finds all Territories that are adjacent to the specified Territory
//
/// \param t -- pointer to a Territory object
/// \return all Territories that are adjacent to the specified Territory
FakeGameMap::TerritoryList FakeGameMap::adjacencies(Territory *) const{
   return tList;
}

/// Finds all Territories that are owned by the specified Player
//
/// \param p -- pointer to a Player object
/// \return all Territories owned by the given player
///
/// \todo do we need this? if we do, it's badly named. using 'filter'
///       method should be just as easy.
/// \depracated
FakeGameMap::TerritoryList FakeGameMap::players(Player * p) const{
   p->name();
   TerritoryList::const_iterator it;
   it = tList.begin();
   return tList;
}

/// Retrieves all Territories that match the specified predicate.
///
/// \param predicate A functor to decide membership in the output list.
///
/// \return the list of TerritoryList selected by the supplied predicate.
FakeGameMap::TerritoryList FakeGameMap::filter(TerritoryOperation * predicate) const{
   (void)predicate;
   /*
     bool a = (*predicate)(t1);
     if (a)
      a=false;
      delete t1;
   */
   return tList;
}

//mutators
/// Traverses all territories and performs the specified operation
//
/// \param op -- operation to be performed
/// \param start -- Territory to start with
void FakeGameMap::traverse(TerritoryOperation * op, Territory * start){
   (void)op;(void)start;return;
}
