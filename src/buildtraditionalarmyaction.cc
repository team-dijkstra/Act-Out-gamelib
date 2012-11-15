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
#include "buildtraditionalarmyaction.h"
#include "phase.h"
#include "territory.h"
#include "traditionalarmy.h"

BuildTraditionalArmyAction::BuildTraditionalArmyAction(Phase* p, Unit * par):aName("BuildTraditionalArmy"), aPhase(p), parent(par)
{}

std::string BuildTraditionalArmyAction::name() const
{
   return aName;
}

bool BuildTraditionalArmyAction::applicable(Phase* p) const
{
   if(p==aPhase)
      return true;
   return false;
}

void BuildTraditionalArmyAction::doaction(int nUnits, Territory* T)
{
   Unit* newArmy;
   newArmy = new TraditionalArmy(T, nUnits);
   /// \todo put this unit in territory's unit container??
   T->addUnit(newArmy);
   delete newArmy;//temporary fix
}
