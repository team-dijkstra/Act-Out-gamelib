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
/// \brief Interface file for the game units -- unit.h
//
/// Specified behaviour of game units

#ifndef FAKEUNIT_H
#define FAKEUNIT_H

#include "unit.h"

class Territory;
class Action;

///An interface to specify the behaviour of the game units
class FakeUnit : public Unit{
  public:
//   FakeUnit(int nunit, Territory * t, std::vector<Action*> uActs);
   FakeUnit(int nunit, Territory * t, std::string s="FakeUnit");
   ~FakeUnit() {}

   //mutators
   /// Increases the numUnits in this FakeUnit
   //
   /// \param a Unit object
   //
   /// \post increases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after increase
   ///         method is performed
   int increase (int u);

   /// Decreases the numUnits in this FakeUnit
   //
   /// \param a Unit object
   //
   /// \post decreases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after decrease
   ///         method is performed
   int decrease (int u);

   Unit * split(int num){return new FakeUnit(num, tWhere);}

   int merge(Unit * u){return nUnits;}
   
   //accessors
   /// \return the current numUnits in this object
   int numUnits() const;

   /// \return the Territory where this FakeUnit is located
   Territory* whereAt() const;

   /// \return the type name of this object
   std::string name() const;

   /// \return all the possible actions that this unit can perform
   std::vector<Action*> actions() const;

  private:
   int nUnits;
   Territory * tWhere;
   std::string uName;
   Unit::actionContainer uActions;

};

#endif
