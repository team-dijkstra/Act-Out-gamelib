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
/// \file
/// \brief Interface file for StlGameMap Class -- stlgamemap.h
/// 
/// StlGameMap interface, specifies behaviour for game maps. 
/// This is currently experimental.

#ifndef STL_GAMEMAP_H
#define STL_GAMEMAP_H

#include <vector>
#include <string>
#include <utility>
#include "gamemap.h"

class Player;
class Territory;
class TerritoryOperation;


/// @copydoc
class StlGameMap : public GameMap {
  public:
   typedef GameMap::TerritoryList TerritoryList; ///< vector of pointers to territories
   
   typedef GameMap::Adjacency Adjacency;///< pair of pointers to territories
   
   typedef GameMap::AdjacencyList AdjacencyList;///< vector of adjacencies
   
   //constructors

   /// \param adjacent -- used to monitor adjacencies
   ///
   /// 
   StlGameMap(const AdjacencyList & adjacent);

   //destructor
   
   ~StlGameMap(); 

   //accessors
   
   /// @copydoc GameMap::begin()
   Territory* begin() const;

   //accessors
   /// @copydoc GameMap::find()
   Territory* find(TerritoryName fn) const;

   /// @copydoc GameMap::adjacencies()
   TerritoryList adjacencies(const Territory * t) const;

   /// @copydoc GameMap::players()
   TerritoryList players(Player * p) const;

   /// @copydoc GameMap::filter()
   TerritoryList filter(TerritoryOperation * predicate) const; 
      
   //mutators
   
   /// @copydoc GameMap::traverse()
   void traverse(TerritoryOperation * op, Territory * start);
  private:
   typedef std::pair<Territory*, TerritoryList> MapNode; ///< pair of Territory and TerritoryList
   typedef std::vector<MapNode> MapType; ///< vector of MapNodes

   MapType territories; ///< this is the map to be used
};

#endif
