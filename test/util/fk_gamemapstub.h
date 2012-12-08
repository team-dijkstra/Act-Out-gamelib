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

#ifndef FK_GAMEMAP_H
#define FK_GAMEMAP_H

#include <vector>
#include <utility>
#include <string>
#include "gamemap.h"

class Player;
class Territory;
class TerritoryOperation;

/// The FK_GameMap class.
//
/// This class is reponsible for representing the collection of Territories in the
/// game, returning relevant information and performing operations on specified TerritoryList 
class FakeGameMap : public GameMap {
  public:

   typedef GameMap::TerritoryList TerritoryList;
   typedef GameMap::Adjacency Adjacency;
   typedef GameMap::AdjacencyList AdjacencyList;
  
  public:
   FakeGameMap(TerritoryList tl, AdjacencyList al);
   ~FakeGameMap();

   //accessors
   /// \return the start territory. Which territory this is is implementation
   ///       defined.
   Territory* begin() const;
   
   /// Finds the specified Territory
   //
   /// \param tname -- string representing the TerritoryName
   /// \return the specified Territory, or a sentinel if not found.
   /// \see StlGameMap::end the sentinel node of this class.
   Territory* find(TerritoryName) const;

   /// Finds all Territories that are adjacent to the specified Territory
   //
   /// \param t -- pointer to a Territory object
   /// \return all Territories that are adjacent to the specified Territory
   TerritoryList adjacencies(const Territory *) const;

   /// Finds all Territories that are owned by the specified Player
   //
   /// \param p -- pointer to a Player object
   /// \return all Territories owned by the given player
   ///
   /// \todo do we need this? if we do, it's badly named. using 'filter'
   ///       method should be just as easy.
   /// \deprecated
   TerritoryList players(Player *) const;

   /// Retrieves all Territories that match the specified predicate.
   ///
   /// \param predicate A functor to decide membership in the output list.
   ///
   /// \return the list of TerritoryList selected by the supplied predicate.
   TerritoryList filter(TerritoryOperation * predicate) const;

   //mutators
   /// Traverses all territories and performs the specified operation
   //
   /// \param op -- operation to be performed
   /// \param start -- Territory to start with
   void traverse(TerritoryOperation * op, Territory * start);

  private:
   TerritoryList tList;
   AdjacencyList aList;
   Territory * t1;
//   TerritoryList::const_iterator const_it;
   
 
};

#endif
