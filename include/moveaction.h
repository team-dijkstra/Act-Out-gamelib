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
#include "action.h"

namespace game {

class Unit;
class Territory;
class Phase;

/**
 * Implements Action interface class.
 *
 * This class is responsible for moving units of one type between
 * territories
 */
class MoveAction : public Action {
/** \todo template this for different types of unit and store the parent unit object
          template<typename U> */
 public:

   //constructors

   /// \param p -- pointer to current Phase
   /// \param par -- pointer to parent Unit
   //
   /// \post MIL:
   ///       <br>- sets aPhase to a p
   ///       <br>- sets parent to par
   MoveAction(Phase * p, Unit * par);
   
   //destructor
	
   ~MoveAction() {}

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
   Phase * aPhase; //! @copydoc AttritonAttackAction::aPhase
   Unit * parent; //! @copydoc AttritionAttackAction::parent
};

}

#endif
