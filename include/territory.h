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

/** \file territory.h
 * \brief contains interface class Territory
 * Territory interface class
 */

#ifndef TERRITORY_H
#define TERRITORY_H

#include <string>
#include <map>

class UnitOperation;

namespace game {

class Player;
class Unit;

/// An interface class to represent a Territory 
class Territory {
  public:
   /// container of references to Unit objects 
   typedef std::map<std::string, Unit*> unitContainer;

   //destructor
   
   virtual ~Territory() {}

   //accessors
   
   /// \return pointer to Player that owns this Territory
   virtual Player* owner() const =0;
   
   /// \return string, name of Territory
   virtual std::string name() const =0;

   /// \param f -- pointer to UnitOperation for filtering Units returned
   //
   /// \return unitContainer of Units on this Territory
   virtual unitContainer units(UnitOperation * f) const =0;

   //mutators
   
   /// \param p -- pointer to Player
   //
   /// \post sets Territory owner to passed Player
   virtual void owner(Player * p) =0;

   /// \param u -- pointer to Unit
   //
   /// \post adds Unit pointer to this Territory's unitContainer
   virtual void addUnit(Unit * u) =0;
};

}

#endif
