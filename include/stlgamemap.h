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
/**
 * \file stlgamemap.h - Interface file for StlGameMap Class.
 * 
 * Provides an STL based implementation of the GameMap interface.
 *
 * \warning This is currently experimental.
 */

#ifndef STL_GAMEMAP_H
#define STL_GAMEMAP_H

#include <vector>
#include <string>
#include <utility>
#include "gamemap.h"

class Player;
class Territory;
class TerritoryOperation;


/**
 * \class StlGameMap
 *
 * The Stl GameMap is implemented using an STL vector of nodes with separate 
 * chaining for the adjacencies. The nodes are stored in sorted order, so
 * searches are guaranted to occur in \f$O(\log(n))\f$ time, and will consume
 * \f$2n\$f space + the overhead for an STL vector. Vector was chosen to 
 * provide good locality of reference for fast cache friendly accesses.
 *
 * \note This class assumes ownership of all supplied Territory objects, and will
 *  clean them up when it's destructor is called. Clients should not delete any 
 *  supplied territories, and should allocate any supplied Territory objects with
 *  \c new. Attempting to supply stack allocated objects will result in undefined
 *  behavior.
 */
class StlGameMap : public GameMap {
  public:
   typedef GameMap::TerritoryList TerritoryList; ///< vector of pointers to territories \see GameMap::TerritoryList
   
   typedef GameMap::Adjacency Adjacency;///< pair of pointers to territories \see GameMap::Adjacency
   
   typedef GameMap::AdjacencyList AdjacencyList;///< vector of adjacencies \see GameMap::AdjacencyList
   
   //constructors

   /**
    * Constructor
    *
    * Sets up the map. Ensures that adjacent pairs are bidirectionally linked, and that the 
    * map elements are stored in the proper order for efficient searches.
    *
    * \param adjacent -- The list of elements that should be stored as bidrectionally adjacent, 
    *   specified as a list of pairs. The supplied territories must be allocated with \c new.
    */ 
   StlGameMap(const AdjacencyList & adjacent);

   /**
    * Destructor
    *
    * Deletes all supplied Territory objects when this object is deleted or goes out of scope.
    */
   ~StlGameMap(); 

   //accessors
   
   /// @copydoc GameMap::begin()
   Territory* begin() const;

   //accessors
   /// @copydoc GameMap::find()
   ///
   /// \note This opperation is guaranteed to run in \f$O(\log(n))\f$ time.
   ///
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
