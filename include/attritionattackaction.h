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
/// AttritionAttackAction class interface, specifies behavious of game actions

/// \file
/// \brief contains the interface class Action -- action.h
//
/// AttritionAttackAction class interface, specifies behavious of game actions

#ifndef ATTRITIONATTACKACTION_H
#define ATTRITIONATTACKACTION_H

#include <string>
#include "territory.h"
#include "phase.h"
#include "action.h"
//class Territory;
//class Phase;

///Basic interface specifying behaviour for class Action
//
///AttritionAttackAction move numUnits from one Territory to another

/// \todo template this for different types of unit and store the parent unit object
					   //template<typename U>
class AttritionAttackAction : public Action{
  public:
   AttritionAttackAction(Unit * p);
   AttritionAttackAction(Unit * p, Phase * ph);
   ~AttritionAttackAction();

   //accessors
   /// \return the name of the action class
   std::string name() const;
   

   /// \return true if action can be used in the specified Phase; false otherwise
   bool applicable(Phase* p) const;

   
   //mutators
   /// \param nUnits -- the number of units to commit to current action
   /// \param T -- the territory to act on.
   //
   /// \post preforms Action on the specified territory using specifiec number of units
   void doaction(int nUnits, Territory * T);


      private:
   Unit * parent;
   const Phase * aPhase;
};

//#include "../src/moveaction.cc"
#endif
