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
/// \brief contains the interface class Action -- action.h
//
/// Action class interface, specifies behavious of game actions

#ifndef ACTION_H
#define ACTION_H

#include <string>

class Territory;
class Phase;

///Basic interface specifying behaviour for class Action
//
///Actions mutate game state.
class Action {
  public:
   virtual ~Action() {}

   //accessors
   /// \return the name of the action class
   virtual std::string name() const =0;

   /// \return true if action can be used in the specified Phase; false otherwise
   virtual bool applicable(Phase* p) const =0;

   //mutators
   /// \param nUnits  -- the number of units to commit to current action
   /// \param T -- the territory to act on.
   //
   /// \post preforms Action on the specified territory using specifiec number of units
   virtual void doaction(int nUnits,Territory* T) =0;
    
};

#endif
