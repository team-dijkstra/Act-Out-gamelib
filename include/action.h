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

class Unit;
class Territory;
class Phase;

/**
 *  Basic interface specifying behaviour for class Action
 *
 *  Actions mutate game state.
 */
class Action {
  public:

   //destructor
   
   virtual ~Action() {}

   //accessors
   
   /// \return name of the action class
   virtual std::string name() const =0;

   /// \param p -- pointer to the current Phase.
   /// \return true if action can be used in the specified Phase; false
   ///         otherwise
   virtual bool applicable(Phase * p) const =0;

   virtual const Unit * unit() const =0;
   virtual const Territory * source() const =0;
   
   //mutators
   
   /// \param nUnits -- integer of the count to do the current action
   /// \param T -- pointer to the territory to act on
   //
   /// \post preforms Action on the territory using a count of nUnits
   virtual void doaction(int nUnits, Territory * T) =0;
    
};

#endif
