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
//
/// StlGameMap interface, specifies behaviour for game maps

#ifndef STL_GAMEMAP_H
#define STL_GAMEMAP_H

#include <vector>
#include <map>
#include <string>
#include "gamemap.h"

class Player;
class Territory;
class TerritoryOperation;

typedef std::map<Territory*, Territory*> TerritoryConnections;

/// \copydoc
class StlGameMap : public GameMap {
  public:

   /// Constructor
   StlGameMap(const TerritoryList & tl, const TerritoryConnections & c);
   ~StlGameMap(); 

   //accessors
   /// \copydoc 
   Territory* find(TerritoryName) const;

   /// \copydoc 
   TerritoryList adjacencies(Territory *) const;

   /// \copydoc 
   TerritoryList players(Player *) const;

   /// \copydoc
   TerritoryList filter(TerritoryOperation * op) const; 
      
   //mutators
   /// \copydoc 
   void traverse(TerritoryOperation * op, Territory * start);
   
};

#endif
