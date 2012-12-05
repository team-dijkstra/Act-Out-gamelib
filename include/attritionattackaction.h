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

/** \file attritionattackaction.h
 * \brief contains the interface class Action
 *
 *  AttritionAttackAction class interface, specifies behavious of game actions
 */
#ifndef ATTRITIONATTACKACTION_H
#define ATTRITIONATTACKACTION_H

#include <string>
#include "territory.h"
#include "phase.h"
#include "action.h"

/**
 * Implements Action interface class
 *
 * AttritionAttackAction attacks with numUnits from a unit on one territory
 * to another unit of the same type on another territory.
 */
class AttritionAttackAction : public Action{
/// \todo template AttritionAttackAction class for different types of unit and store the parent unit object
      public:

   //constructors

   /// \param p -- pointer to parent Unit
   //
   /// \post MIL:
   ///       <br>- sets parent to p
   ///       <br> sets aPhase to a pointer to the Phase where this action is
   ///       applicable
   AttritionAttackAction(Unit * p);

   /// \param p -- pointer to the parent Unit
   /// \param ph -- pointer to current Phase
   //
   /// \post MIL:
   ///       <br>- sets parent to p
   ///       <br>- sets aPhase to ph
   AttritionAttackAction(Unit * p, Phase * ph);

   //destructor
   
   ~AttritionAttackAction();

   //accessors
   
   //! @copydoc Action::name()
   std::string name() const;
   

   //! @copydoc Action::applicable()
   bool applicable(Phase* p) const;

   const Unit * unit() const;
   const Territory * source() const;

   //mutators
   
   //! @copydoc Action::doaction()
   void doaction(int nUnits, Territory * T);

      private:
   
   Unit * parent; ///< pointer to the Unit that does this action
   Phase * aPhase; ///< pointer to the Phase that applies to this action
   bool mustDelete;
};

//#include "../src/moveaction.cc"
#endif
