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
#include "builderunit.h"
#include "territory.h"
#include "action.h"

BuilderUnit::BuilderUnit(Territory * t, int nunit):  uTerritory(t), nUnits(nunit), uName("BuilderUnit")
{}

int BuilderUnit::increase (Unit* u)
{
   nUnits += u->numUnits();
   return nUnits;
}

int BuilderUnit::decrease (Unit* u)
{
   int tdec = u->numUnits();
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

int BuilderUnit::numUnits() const{
   return nUnits;
}

Territory* BuilderUnit::whereAt() const{
   return uTerritory;
}

std::string BuilderUnit::name() const{
   return uName;
}

std::vector<Action*> BuilderUnit::actions() const{}
