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
/// \brief contains interface class Territory -- territory.h
//
/// Territory interface class
#ifndef LAND_TERRITORY_H
#define LAND_TERRITORY_H

#include <map>
#include "territory.h"

/// An interface class to represent a Territory 
class LandTerritory : public Territory{
  public:
   LandTerritory(std::string nm, Player* own);
   ~LandTerritory() {}

   //accessors
   /// \return the Player object that currently owns this Territory
   Player* owner() const;
   
   /// \return a string, the name of the Territory
   std::string name() const;

   /// \param[in] 
   /// \return a vector of Units that are on this Territory 
   unitContainer units(Filter* f) const;

   //mutators
   /// \param[in] reference to Player object 
   /// \post sets Territory owner to the passed Player object
   void owner(Player*);

   /// \todo possible better method
   void addUnit(Unit *);

  private:
   
   std::string tName;
   Player * tOwner;
   unitContainer tUnits;
   
};

#endif
