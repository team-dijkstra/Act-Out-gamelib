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
/// \file altgamemap.cc
/// \brief Implementation file for AltGameMap Class 
//
/// Alt class implements GameMap interface.
#include <vector>
#include <utility>
#include <string>

#include "altgamemap.h"
#include "player.h"
#include "territory.h"
#include "phase.h"
#include "filterbyterritoryowner.h"

AltGameMap::AltGameMap(m_adjList list): altMap(list)
{
   //std::cout << "\n The size of the game map on constructions: "<< altMap.size() << "\n";
}
			     
AltGameMap::~AltGameMap() {
   //gamemap should delete its own territories
   m_adjList::iterator it;
   for (it=  altMap.begin(); it != altMap.end(); ++it)
   {
      delete (it->first);
   }
}
  
//accessors
/// \return the start territory. Which territory this is is implementation
///       defined.
Territory* AltGameMap::begin() const{
   AltGameMap::m_adjList::const_iterator mt;
   mt =  altMap.begin();
   return mt->first;
}
   
/// Finds the specified Territory
//
/// \param tname -- string representing the TerritoryName
/// \return the specified Territory, or a sentinel if not found.
/// \see StlGameMap::end the sentinel node of this class.
Territory* AltGameMap::find(TerritoryName fn) const{
   AltGameMap::m_adjList::const_iterator mt;
   for( mt = altMap.begin(); mt != altMap.end(); ++mt)
   {
      std::string name = (mt->first)->name();
      if (name == fn)
      {
	 return mt->first;
      }
   }
   return NULL;
}

/// Finds all Territories that are adjacent to the specified Territory
//
/// \param t -- pointer to a Territory object
/// \return all Territories that are adjacent to the specified Territory
AltGameMap::TerritoryList AltGameMap::adjacencies(Territory * t) const{
   m_adjList::const_iterator mt;
   mt = altMap.find(t);
   return mt->second;
}

/// Finds all Territories that are owned by the specified Player
//
/// \param p -- pointer to a Player object
/// \return all Territories owned by the given player
///
/// \todo do we need this? if we do, it's badly named. using 'filter'
///       method should be just as easy.
/// \depracated
AltGameMap::TerritoryList AltGameMap::players(Player * p) const{
   std::string pname = p->name();
   TerritoryOperation * pop = new FilterByTerritoryOwner(pname);
   TerritoryList tmp;
   tmp = filter(pop);
   delete pop;
   return tmp;
}

/// Retrieves all Territories that match the specified predicate.
///
/// \param predicate A functor to decide membership in the output list.
///
/// \return the list of TerritoryList selected by the supplied predicate.
AltGameMap::TerritoryList AltGameMap::filter(TerritoryOperation * predicate) const{
   m_adjList::const_iterator mt;
   TerritoryList tmp;
   
   for( mt = altMap.begin(); mt != altMap.end(); ++mt)
   {
      bool check = (*predicate)(mt->first);
      if (check)
      {
	 tmp.push_back(mt->first);
      }
   }
   return tmp;
}

//mutators
/// Traverses all territories and performs the specified operation
//
/// \param op -- operation to be performed
/// \param start -- Territory to start with
void AltGameMap::traverse(TerritoryOperation * op, Territory * start){
   (void)op;(void)start;
   /*
   m_adjList::iterator mt;
   for( mt = altMap.begin(); mt != altMap.end(); ++it)
   {
      bool check = op->(mt.first);
      if (check)
      {
	 
      }
      }
   */
}
