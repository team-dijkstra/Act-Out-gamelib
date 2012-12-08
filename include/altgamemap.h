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
/// \file altgamemap.h
/// \brief Interface file for AltGameMap Class 
//
/// Alt class implements GameMap interface.

#ifndef ALT_GAMEMAP_H
#define ALT_GAMEMAP_H

#include <vector>
#include <utility>
#include <string>
#include <map>
#include "gamemap.h"

class Player;
class Territory;
class TerritoryOperation;

/// TerritoryName typedef is for clarity and code readability
typedef std::string TerritoryName;   

/// The AltGameMap class.
//
/// This class is reponsible for representing the collection of Territories in the
/// game, returning relevant information and performing operations on specified TerritoryList.
/// Deletes all territories.
class AltGameMap : public GameMap {
  public:

   typedef GameMap::TerritoryList TerritoryList; ///< \typedef vector of pointers to territories
   
   typedef GameMap::Adjacency Adjacency; ///< \typedef pair of pointers to territories
   
   typedef GameMap::AdjacencyList AdjacencyList; ///< \typedef vector of adjacencies

   typedef std::map< Territory * , TerritoryList > m_adjList; ///< The adjacencylist type used by this implementation
   
   /// Constructor. Initializes the map with the specified adjacencies.
   /// Self adjacencies will be eliminated.
   ///  
   /// \param list A list of adjacent territories.
   /// 
   /// \see GameMap::AdjacencyList for the format of the adjacency list.
   ///
   AltGameMap(m_adjList list);

   /// Destructor. Deletes all stored territories.
   ~AltGameMap();

   //accessors
   
   /// @copydoc GameMap::begin()
   Territory* begin() const;
   
   /// @copydoc GameMap::find()
   Territory* find(TerritoryName fn) const;

   /// @copydoc GameMap::adjacencies()
   TerritoryList adjacencies(const Territory * t) const;

   /// @copydoc GameMap::players()
   TerritoryList players(Player * p) const;

   /// @copydoc GameMap::filter()
   TerritoryList filter(TerritoryOperation * predicate) const;

   /// @copydoc GameMap::traverse()
   void traverse(TerritoryOperation * op, Territory * start = NULL);

  private:
   //TerritoryList tList;
   //AdjacencyList aList;
   m_adjList altMap;
   
 
};

#endif
