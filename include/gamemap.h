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
/// \brief Interface file for GameMap Class -- gamemap.h
//
/// GameMap interface, specifies behaviour for game maps

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <utility>
#include <string>

namespace game {
   class Player;
   class Territory;
}

class TerritoryOperation;

/// TerritoryName typedef is for clarity and code readability
typedef std::string TerritoryName;

/// The GameMap interface class.
//
/// This class is reponsible for representing the collection of Territories in the
/// game, returning relevant information and performing operations on specified TerritoryList 
class GameMap {
  public:
   
   typedef std::vector<game::Territory*> TerritoryList;
   typedef std::pair<game::Territory*, game::Territory*> Adjacency;
   typedef std::vector<Adjacency> AdjacencyList;


   virtual ~GameMap() {}
    
   //constants
   /// \return a sentinel node. Used to indicate non-existent values.
   static const game::Territory* end() {return NULL;}

   //accessors
   /// \return the start territory. Which territory this is is implementation
   ///       defined.
   virtual game::Territory* begin() const =0;
   
   /// Finds the specified Territory
   //
   /// \param tname -- string representing the TerritoryName
   /// \return the specified Territory, or a sentinel if not found.
   /// \see StlGameMap::end the sentinel node of this class.
   virtual game::Territory* find(TerritoryName) const =0;

   /// Finds all Territories that are adjacent to the specified Territory
   //
   /// \param t -- pointer to a Territory object
   /// \return all Territories that are adjacent to the specified Territory
   virtual TerritoryList adjacencies(game::Territory *) const =0;

   /// Finds all Territories that are owned by the specified Player
   //
   /// \param p -- pointer to a Player object
   /// \return all Territories owned by the given player
   ///
   /// \todo do we need this? if we do, it's badly named. using 'filter'
   ///       method should be just as easy.
   /// \deprecated This operation can be easily replaced by filter() with
   ///       a player name filter.
   virtual TerritoryList players(game::Player *) const =0;

   /// Retrieves all Territories that match the specified predicate.
   ///
   /// \param predicate A functor to decide membership in the output list.
   ///
   /// \return the list of TerritoryList selected by the supplied predicate.
   virtual TerritoryList filter(TerritoryOperation * predicate) const =0;

   //mutators
   /// Traverses all territories and performs the specified operation
   //
   /// \param op -- operation to be performed
   /// \param start -- Territory to start with
   virtual void traverse(TerritoryOperation * op, game::Territory * start) =0;

};

#endif
