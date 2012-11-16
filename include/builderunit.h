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

#ifndef BUILDER_UNIT_H
#define BUILDER_UNIT_H

#include "unit.h"

///An interface to specify the behaviour of the game units
class BuilderUnit : public Unit {
  public:
   BuilderUnit(Territory *, int nunit=1);
   ~BuilderUnit() {}

   //mutators
   
   /// \brief Increases the numUnits in this Unit
   //
   /// \param u -- an integer, the amount to increase the count in this Unit
   //
   /// \post increases the numUnits in this object by u
   //
   /// \return the current numUnits in this object after increase method is
   ///         performed
   int increase (int u);

   /// \brief Decreases the numUnits in this Unit
   //
   /// \param u -- an integer, the amount to decrease the count in this Unit
   //
   /// \post decreases the numUnits in this object by u
   //
   /// \return the current numUnits in this object after decrease method is performed
   int decrease (int u);

   /// \brief Splits the Unit in to two Units
   //
   /// \param num -- an integer that specifies the count to split from the
   ///               current unit; defaults to 1
   //
   /// \post the count of this Unit is decreased by num, and the returned Unit
   ///       can do an action with num count
   //
   /// \return the Unit that was split from this Unit
   Unit * split(int num=1);

   /// \brief Merges the Units together
   //
   /// \param u -- a pointer to a Unit that is to be merged with this Unit
   //
   /// \post this Unit now has count increased by the count of u, and u is
   ///       deleted
   //
   /// \return an integer of the count in this Unit after the merge
   int merge(Unit * u);
   
   //accessors

   /// \return the current numUnits in this object
   int numUnits() const;

   /// \return the Territory where this Unit is located
   Territory* whereAt() const;

   /// \return the type name of this object
   std::string name() const;

   /// \return all the possible actions that this unit can perform
   std::vector<Action*> actions() const;

  private:

   
   Territory * uTerritory; ///< the Territory the Unit is placed
   int nUnits; ///< the count of this Unit
   std::string uName; ///< the name of the Unit; for specifying Unit type
   std::vector<Action*> uActions; ///< a list of actions that this Unit is able
   ///<                                to perform
   
};

#endif
