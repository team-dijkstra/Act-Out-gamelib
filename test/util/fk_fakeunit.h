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
/** \file fk_fakeunit.h
 * Contains a Test class to implement the Unit interface
 */
#ifndef FAKEUNIT_H
#define FAKEUNIT_H

#include "unit.h"

namespace game {
   class Territory;
   class Action;
}

///An interface to specify the behaviour of the game units
class FakeUnit : public game::Unit {
  public:

   //constructors
//   FakeUnit(int nunit, Territory * t, std::vector<Action*> uActs);

   /// \param nunit -- integer, count of this Unit
   /// \param t -- pointer to Territory Unit is on
   /// \param s -- string, name of Unit
   //
   /// \post MIL:
   ///       <br>- sets nUnits to nunits
   ///       <br>- sets uTerritory to t
   ///       <br>- sets uName to "FakeUnit"
   FakeUnit(int nunit, game::Territory * t, std::string s="FakeUnit");

   //destructor
   
   ~FakeUnit() {}

   //mutators
   
   /// \brief Increases the numUnits in this Unit
   //
   /// \param u -- integer of the amount to increase the count in this Unit
   //
   /// \post increases the count in this object by u
   //
   /// \return count in this object after increase method is performed
   int increase (int u);

   /// \brief Decreases the numUnits in this Unit
   //
   /// \param u -- integer of the amount to decrease the count in this Unit
   //
   /// \post decreases the count in this object by u
   //
   /// \return count in this object after decrease method is performed
   int decrease (int u);

   /// \brief Splits the Unit in to two Units
   //
   /// \param num -- integer that specifies the count to split from the unit;
   ///               defaults to 1
   //
   /// \post count of this Unit is decreased by num, returned Unit can do an
   ///       action with num count
   //
   /// \return Unit that was split from this Unit
   game::Unit * split(int num){return new FakeUnit(num, tWhere);}

   /// \brief Merges the Units together
   //
   /// \param u -- pointer to a Unit that is to be merged with this Unit
   //
   /// \post this Unit now has count increased by the count of u, u is deleted
   //
   /// \return integer of the count in this Unit after the merge 
   int merge(game::Unit * u){return u->numUnits();}
   
   //accessors
   
   /// \return current count in this object
   int numUnits() const;

   /// \return pointer to the Territory where this Unit is located
   game::Territory* whereAt() const;

   /// \return type name of this object
   std::string name() const;

   /// \return vector of pointers of all possible actions this unit can perform
   std::vector<game::Action*> actions() const;

  private:
   int nUnits; ///< count of this Unit
   game::Territory * tWhere; ///< pointer to Territory Unit is placed
   std::string uName; ///< type name of this Unit
   Unit::actionContainer uActions; ///< list of actions Unit can perform

};

#endif
