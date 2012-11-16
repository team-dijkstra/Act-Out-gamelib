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

#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

class Territory;
class Action;

///An interface to specify the behaviour of the game units
class Unit {
  public:
   typedef std::vector<Action*> actionContainer;
   virtual ~Unit() {}

   //mutators
   
   /// \brief Increases the numUnits in this Unit
   //
   /// \param u -- integer of the amount to increase the count in this Unit
   //
   /// \post increases the count in this object by u
   //
   /// \return count in this object after increase method is performed
   virtual int increase (int u) =0;

   /// \brief Decreases the numUnits in this Unit
   //
   /// \param u -- integer of the amount to decrease the count in this Unit
   //
   /// \post decreases the count in this object by u
   //
   /// \return count in this object after decrease method is performed
   virtual int decrease (int u) =0;

   /// \brief Splits the Unit in to two Units
   //
   /// \param num -- integer that specifies the count to split from the unit;
   ///               defaults to 1
   //
   /// \post count of this Unit is decreased by num, returned Unit can do an
   ///       action with num count
   //
   /// \return Unit that was split from this Unit
   virtual Unit * split(int num=1) =0;

   /// \brief Merges the Units together
   //
   /// \param u -- pointer to a Unit that is to be merged with this Unit
   //
   /// \post this Unit now has count increased by the count of u, u is deleted
   //
   /// \return integer of the count in this Unit after the merge 
   virtual int merge(Unit * u) =0;
   
   //accessors
   
   /// \return current count in this object
   virtual int numUnits() const =0;

   /// \return pointer to the Territory where this Unit is located
   virtual Territory* whereAt() const =0;

   /// \return type name of this object
   virtual std::string name() const =0;

   /// \return vector of pointers of all possible actions this unit can perform
   virtual actionContainer actions() const =0;
   
};

#endif
