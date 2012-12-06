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
/**
 *  \file moveaction.h
 *
 *  Implements Action interface class.
 */
#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <string>
#include "defaultaction.h"

class Territory;
class Phase;
class Unit; 

/**
 * Implements Action interface class.
 *
 * This class is responsible for moving units of one type between
 * territories
 */
class MoveAction : public DefaultAction {
 public:

   static const std::string NAME; 
   
   //constructors
   //========================================================================//

   /// Constructor
   ///
   /// \param p -- pointer to current Phase. not used.
   /// \param par -- pointer to parent Unit
   ///
   /// \deprecated This constructor is provided to preserve compatibility with
   ///  existing tests.
   MoveAction(Phase * p, Unit * par);

   /// Constructor
   ///
   /// \param par A pointer to the parent unit of this action. Conceptually
   ///  this is the unit performing the action.
   ///
   MoveAction(Unit * par);
   
   //accessors
   //========================================================================//
   
   //! @copydoc Action::name()
   std::string name() const;

   //! @copydoc Action::applicable()
   bool applicable(Phase* p) const;

   //mutators
   //========================================================================//
   
   //! @copydoc Action::doaction()
   void doaction(int nUnits, Territory * T);
};

//#include "../src/moveaction.cc"
#endif
