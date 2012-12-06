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

/** \file builderunit.cc 
 * Implementation file for BuilderUnit class
 * Detatailed descriptions of each method are in the header file
 */
#include "builderunit.h"
#include "territory.h"
#include "action.h"
#include "buildtraditionalarmyaction.h"

BuilderUnit::BuilderUnit(Territory * t, int nunit):  uTerritory(t), nUnits(nunit), uName("BuilderUnit")
{
   uActions.push_back(new BuildTraditionalArmyAction(this));
}

BuilderUnit::~BuilderUnit(){
   actionContainer::iterator it;
   for(it = uActions.begin(); it != uActions.end(); ++it)
      delete *it;
}
			     
int BuilderUnit::increase (int u)
{
   nUnits += u;
   return nUnits;
}

int BuilderUnit::decrease (int u)
{
   int tdec = u;
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

Unit * BuilderUnit::split (int num)
{
   if(num > numUnits())
      num = numUnits();
   this->decrease(num);
   return new BuilderUnit(whereAt(),num);
}

int BuilderUnit::merge (Unit * u){
   int n = u->numUnits();
   this->increase(n);
   delete u;
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

Unit::actionContainer BuilderUnit::actions() const{ 
   return uActions;
}
