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
 * \file buildtraditionalarmyaction.h
 * 
 * Implementation file for BuildTraditionalArmyAction class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef BUILD_TRADITIONAL_ARMY_ACTION_H
#define BUILD_TRADITIONAL_ARMY_ACTION_H

#include "defaultaction.h"

class Unit;
class Territory;
class Phase;

/**
 * Implements Action interface class.
 *
 * This class is responsible for constructing instances of
 * TraditionalArmy and placing them on specific instances of
 * LandTerritory
 */
class BuildTraditionalArmyAction : public DefaultAction {
  public:

   /// \see Action::NAME
   static const std::string NAME;

   //constructors
   //========================================================================//

   /// Constructor
   ///
   /// \param p -- pointer to current Phase. not used.
   /// \param par -- pointer to parent Unit
   ///
   /// \deprecated This constructor is included simply to preserve
   ///  compatibility with existing tests.
   BuildTraditionalArmyAction(Phase * p, Unit * par);

   /// Constructor
   ///
   /// \param par A pointer to the parent unit of this action. Conceptually
   ///  this is the unit performing the action.
   ///
   BuildTraditionalArmyAction(Unit * par);
   
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
