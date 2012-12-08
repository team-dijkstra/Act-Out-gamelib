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

   /// Constants indicating the state of the Action implementation.
   enum State {
      READY, //< indicates that the action has not been performed yet and is not pending.
      PENDING, //< indicates that the action has not been performed yet, but has been submitted.
      SUCCEEDED, //< indicates that the action has been performed and succeeded.
      FAILED, //< indicates that the action was attempted, but failed. 
      INVALID, //< indicates that the action failed because it was not valid.
      LAST //< dummy state used as a sentinel, and so we know how many states there are.
   };

   /// Virtual base destructor
   virtual ~Action() {}

   //accessors
   //========================================================================//
   
   /// \return name of the action class
   virtual std::string name() const =0;

   /// Implementations of this function shall construct and return a 
   /// string describing the action including all pertinant information,
   /// such as the source territory, and the type of unit performing the 
   /// action (conceptually).
   ///
   /// \return A string describing the action for top level consumption.
   virtual std::string description() const =0;

   /// Implementations of this function shall construct and return a
   /// string describing the status of the action being performed. Typically
   /// there will be a different string returned:
   ///
   /// 1. Before the operation has been performed indicating that the action
   ///    is pending, or has not been performed yet.
   /// 2. After the operation has been performed, and has succeeded 
   ///    indicating success.
   /// 3. After the operation has been performed, and has failed, indicating 
   ///    failure.
   ///
   /// \return The status of the action as described above.
   ///
   virtual std::string status() const =0;

   /// Implementations of this function shall return one of the defined constants
   /// Providing programatically interperable information on the state of the 
   /// Action.
   /// 
   /// \return the state of the action.
   /// \see Action::ActionState, for the set of values that might be returned.
   ///
   virtual Action::State state() const =0;

   /// Indicates whether or not this Action implementation can be performed in
   /// the supplied phase.
   ///
   /// \param p -- pointer to the current Phase.
   /// \return true if action can be used in the specified Phase; false
   ///         otherwise
   virtual bool applicable(Phase * p) const =0;

   /// \return The parent unit of the Action implementation. Conceptually this
   ///   is the unit that performs the action.
   virtual const Unit * unit() const =0;

   /// \return The source Territory of the unit performing the action.
   virtual const Territory * source() const =0;
   
   //mutators
   //========================================================================//

   /// Preforms Action on the territory using a count of nUnits 
   /// from the source unit.
   ///
   /// \param nUnits -- integer of the count to do the current action
   /// \param T -- pointer to the territory to act on
   ///
   virtual void doaction(int nUnits, Territory * T) =0;

   /// sets the state of the Action to the specified state.
   ///
   /// \param s The state to set the action to. Defaults to Action::State::READY. 
   virtual void setState(Action::State s = Action::State::READY) =0;
    
};

#endif
