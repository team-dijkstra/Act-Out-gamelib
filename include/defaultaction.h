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
/** \file buildtraditionalarmyaction.h
 * Implementation file for BuildTraditionalArmyAction class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef DEFAULT_ACTION_H
#define DEFAULT_ACTION_H

#include <string>
#include "action.h"

class Unit;
class Phase;
class Territory;

/**
 * Partially implements Action interface class. Derived classes are 
 * responsible for implementing Action::doaction(), and should also implement
 * Action::name() and Action::applicable. Stubs are provided for convenience.
 */
class DefaultAction : public Action {
  public:

   static const std::string NAME;
   //constructors

   /// Constructor
   ///
   /// \param par A pointer to the parent unit of this action. Conceptually
   ///  this is the unit performing the action.
   ///
   DefaultAction(Unit * par);

   // no destructor necessary. Action is owned by the parent Unit.
 
   //accessors
   //========================================================================//
   
   //! @copydoc Action::name()
   std::string name() const;

   //! @copydoc Action::description()
   std::string description() const;

   //! @copydoc Action::status()
   std::string status() const;

   //! @copydoc Action::state()
   Action::State state() const;

   //! @copydoc Action::applicable()
   bool applicable(Phase* p) const;

   //! @copydoc Action::unit()
   const Unit * unit() const;

   //! @copydoc Action::source()
   const Territory * source() const;

   //mutators
   //========================================================================//
   
   //! @copydoc Action::setState()
   void setState(Action::State s = Action::State::READY);

  protected:

   static const std::string status_msg [Action::State::LAST];

   /// \todo Should we provide protected accessors for parent? or use it directly?
   
   /// The parent of the Action. Conceptually the parent is the unit 
   /// performing the action.
   Unit * m_parent;

   /// The current state of the action.
   Action::State m_state; 
};

#endif

