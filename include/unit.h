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
   /// Increases the numUnits in this Unit
   //
   /// \param a Unit object
   //
   /// \post increases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after increase
   ///         method is performed
   virtual int increase (Unit* u) =0;

   /// Decreases the numUnits in this Unit
   //
   /// \param a Unit object
   //
   /// \post decreases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after decrease
   ///         method is performed
   virtual int decrease (Unit* u) =0;

   //accessors
   /// \return the current numUnits in this object
   virtual int numUnits() const =0;

   /// \return the Territory where this Unit is located
   virtual Territory* whereAt() const =0;

   /// \return the type name of this object
   virtual std::string name() const =0;

   /// \return all the possible actions that this unit can perform
   virtual std::vector<Action*> actions() const =0;
   
};

#endif
