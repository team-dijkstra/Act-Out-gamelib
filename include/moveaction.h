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
/// MoveAction class interface, specifies behavious of game actions

#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <string>
#include "territory.h"
#include "phase.h"
#include "action.h"
#include "builderunit.h"

//class Territory;
//class Phase;

///Basic interface specifying behaviour for class Action
//
///MoveAction move numUnits from one Territory to another

/// \todo template this for different types of unit and store the parent unit object
					   //template<typename U>
class MoveAction : public Action{
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

   
   //mutators
   
   //! @copydoc Action::doaction()
   void doaction(int nUnits, Territory * T);


      private:
   Phase * aPhase; //! @copydoc AttritonAttackAction::aPhase
   Unit * parent; //! @copydoc AttritionAttackAction::parent
};

//#include "../src/moveaction.cc"
#endif
