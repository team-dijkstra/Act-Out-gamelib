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
#include "traditionalarmy.h"
#include "territory.h"
#include "moveaction.h"

TraditionalArmy::TraditionalArmy(Territory * t, int nunit ): nUnits(nunit), uTerritory(t), uName("TraditionalArmy")
{
   uActions.push_back(new MoveAction(this));

}

/// \todo implement increase units
int TraditionalArmy::increase (Unit* u){
   nUnits += u->numUnits();
   return nUnits;
}

/// \todo implement decrease units
int TraditionalArmy::decrease (Unit* u){
   int tdec = u->numUnits();
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

int TraditionalArmy::numUnits() const{
   return nUnits;
}

Territory* TraditionalArmy::whereAt() const{
   return uTerritory;
}

std::string TraditionalArmy::name() const{
   return uName;
}

std::vector<Action*> TraditionalArmy::actions() const{
   return uActions;
}
