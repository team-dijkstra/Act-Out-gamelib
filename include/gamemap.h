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
#include <string>

class Player;
class Territory;
class Operation;

/// TerritoryName typedef is for clarity and code readability
typedef string TerritoryName;

/// The GameMap interface class.
//
/// This class is reponsible for representing the collection of Territories in the
/// game, returning relevant information and performing operations on specified territories 
class GameMap {
  public:
   virtual ~GameMap() {}

   //accessors
   /// Finds the specified Territory
   //
   /// \param tname -- string representing the TerritoryName
   /// \return the specified Territory
   virtual Territory find(TerritoryName tname) const =0;

   /// Finds all Territories that are adjacent to the specified Territory
   //
   /// \param t -- pointer to a Territory object
   /// \return all Territories that are adjacent to the specified Territory
   virtual std::vector<Territory*> adjacencies(Territory * t) const =0;

   /// Finds all Territories that are owned by the specified Player
   //
   /// \param p -- pointer to a Player object
   /// \return all Territories owned by the given player
   virtual std::vector<Territory*> players(Player * p) const =0;

   //mutators
   /// Traverses all territories and performs the specified operation
   //
   /// \param op -- operation to be performed
   /// \param start -- Territory to start with
   //
   /// \return a list of Territories which have been operated on
   virtual std::vector<Territory*> traverse(Operation * op, Territory * start) =0;
   
};

#endif
