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
/** \file fk_faketerritory.h
 * Contains a Test class to implement the Territory interface
 */
#ifndef FAKETERRITORY_H
#define FAKETERRITORY_H

#include "territory.h"
#include "player.h"

class Unit;

/// An interface class to represent a Territory 
class FakeTerritory : public Territory{
  public:
   FakeTerritory(std::string & n, Player * own = NULL):tName(n), tOwner(own){}
   virtual ~FakeTerritory() {delete tOwner;}

   //accessors
   /// \return the Player object that currently owns this Territory
   Player* owner() const{ return tOwner;}
   
   /// \return a string, the name of the Territory
   std::string name() const{ return tName;}

   /// \param[in] 
   /// \return a vector of Units that are on this Territory 
   unitContainer units(UnitOperation* f) const{ return unitContainer();}

   //mutators
   /// \param[in] p -- pointer to Player object 
   /// \post sets Territory owner to the passed Player object
   void owner(Player* p){(void)p;}

   
   /// \param[in] u -- pointer to a Unit object
   /// \post stores pointer in this territory's unitContainer
   void addUnit(Unit* u){(void)u;}

  private:
   std::string tName;
   Player * tOwner;
   
};

#endif
