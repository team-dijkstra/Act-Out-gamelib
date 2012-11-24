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

   //constructors

   /// \param n -- string, passed by reference, to be this Territory's name
   /// \param own -- pointer to Player to be owner
   //
   /// \post MIL:
   ///       <br>- sets tName to n
   ///       <br>- sets tOwner to own
   FakeTerritory(const std::string & n, Player * own = NULL):tName(n), tOwner(own){}

   //destructor
   
   virtual ~FakeTerritory() {delete tOwner;}

   //accessors
   
   /// \return pointer to Player that owns this Territory
   Player* owner() const{ return tOwner;}
   
   /// \return string, name of Territory
   std::string name() const{ return tName;}

   /// \param f -- pointer to UnitOperation for filtering Units returned
   //
   /// \return unitContainer of Units on this Territory
   unitContainer units(UnitOperation* f) const {
      (void)f; 
      return unitContainer();
   }

   //mutators
   
   /// \param p -- pointer to Player
   //
   /// \post sets Territory owner to passed Player
   void owner(Player* p){(void)p;}

   
   /// \param u -- pointer to Unit
   //
   /// \post adds Unit pointer to this Territory's unitContainer
   void addUnit(Unit* u){(void)u;}

  private:
   std::string tName; ///< string, name of Territory
   Player * tOwner; ///< pointer to Player that is owner of this Territory
   
};

#endif
