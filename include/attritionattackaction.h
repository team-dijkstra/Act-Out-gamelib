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
 * \file attritionattackaction.h
 *
 * AttritionAttackAction class interface, specifies behavious of game actions
 */

#ifndef ATTRITIONATTACKACTION_H
#define ATTRITIONATTACKACTION_H

#include <string>
#include "defaultaction.h"

/**
 * Implements Action interface class
 *
 * AttritionAttackAction attacks with numUnits from a unit on one territory
 * to another unit of the same type on another territory.
 */
class AttritionAttackAction : public DefaultAction {

  public:

   static const std::string NAME;
   
   //constructors

   /// Constructor
   ///
   /// Sets the parent of the Action to p. Conceptually the parent is the unit
   /// performing the Action.
   /// 
   /// \param p -- pointer to parent Unit
   ///
   AttritionAttackAction(Unit * p);

   /// \param p -- pointer to the parent Unit
   /// \param ph -- pointer to current Phase. not used.
   ///
   /// \deprecated This constructor is included to preserve compatiblity with
   /// existing tests.
   AttritionAttackAction(Unit * p, Phase * ph);

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

#endif
