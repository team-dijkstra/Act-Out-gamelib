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
#include <algorithm>

#include "altgamemap.h"
#include "player.h"
#include "territory.h"
#include "phase.h"
#include "filterbyterritoryowner.h"
//#include "debug.h"

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

Territory* AltGameMap::begin() const{
   AltGameMap::m_adjList::const_iterator mt;
   mt =  altMap.begin();
   return mt->first;
}
   
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

AltGameMap::TerritoryList AltGameMap::adjacencies(const Territory * t) const{
   m_adjList::const_iterator mt;
   mt = altMap.find(const_cast<Territory *>(t));
   
   return mt->second;
}

AltGameMap::TerritoryList AltGameMap::players(Player * p) const{
   std::string pname = p->name();
   TerritoryOperation * pop = new FilterByTerritoryOwner(pname);
   TerritoryList tmp;
   tmp = filter(pop);
   delete pop;
   return tmp;
}

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

void AltGameMap::traverse(TerritoryOperation * op, Territory * start){
   (void)start;
   m_adjList::iterator mt;
   //TerritoryList tmp;
   
   for( mt = altMap.begin(); mt != altMap.end(); ++mt)
   {

      //dout << " " << mt->first->owner()->name() << std::endl;
      bool check = (*op)(mt->first);
      //dout << " " << mt->first->owner()->name() << std::endl;
      if (check)
      {
	 //tmp.push_back(mt->first);
      }
   }
   return ;//tmp;
}
