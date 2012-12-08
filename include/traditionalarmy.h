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
/// \brief Interface file for the game units -- unit.h
//
/// Specified behaviour of game units

#ifndef TRADITIONAL_ARMY_H
#define TRADITIONAL_ARMY_H

#include "unit.h"

///An interface to specify the behaviour of the game units
class TraditionalArmy : public Unit {
  public:

   //constructors

   //! @copydoc BuilderUnit::BuilderUnit()
   TraditionalArmy(Territory * t, int nunit=1);

   /// \param applicableActions -- a container of applicable actions
   /// \param t -- pointer to Territory Unit is on
   /// \param nunit -- integer, count of this Unit
   ///
   /// sets uTerritory to t, sets nUnits to nunits,
   /// sets uName to name of this Unit, sets uActions to applicableActions
   TraditionalArmy(Territory * t, int nunit, Unit::actionContainer applicableActions );

   // destructor
   
   /// Destructor. Deletes its actions.
   ~TraditionalArmy();

   //mutators

   //! @copydoc Unit::increase()
   int increase (int u);

   //! @copydoc Unit::decrease()
   int decrease (int u);

   //! @copydoc Unit::split()
   Unit * split(int num=1);

   //! @copydoc Unit::merge()
   int merge(Unit * u);
   
   //accessors
   
   //! @copydoc Unit::numUnits()
   int numUnits() const;

   //! @copydoc Unit::whereAt()
   Territory* whereAt() const;

   //! @copydoc Unit::name()
   std::string name() const;

   //! @copydoc Unit::actions()
   std::vector<Action*> actions() const;

   //TraditionalArmy specific mutator

   /// sets uActions to acts
   /// \param acts -- a container of actions
   void setActions(Unit::actionContainer acts);
   

  private:
   int nUnits; //! @copydoc BuilderUnit::nUnits
   Territory * uTerritory; //! @copydoc BuilderUnit::uTerritory
   std::string uName;  //! @copydoc BuilderUnit::uName
   Unit::actionContainer uActions;  //! @copydoc BuilderUnit::uAction
   
};

#endif
