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
/** \file traditionalarmy.cc
 * Implementation file for TraditionalArmy class
 * Detatailed descriptions of each method are in the header file
 */
#include <stdexcept>
#include "traditionalarmy.h"
#include "territory.h"
#include "moveaction.h"
#include "defaultphase.h"

using namespace game;

TraditionalArmy::TraditionalArmy(Territory * t, int nunit ): nUnits(nunit), uTerritory(t), uName("TraditionalArmy")
{
   DefaultPhase dp(std::string("Marshall"));
   uActions.push_back(new MoveAction(&dp, this));

}

TraditionalArmy::~TraditionalArmy(){
   actionContainer::iterator it;
   for(it = uActions.begin(); it != uActions.end(); ++it)
      delete *it;
}

/// \todo implement increase units
int TraditionalArmy::increase (int u){
   nUnits += u;
   return nUnits;
}

/// \todo implement decrease units
int TraditionalArmy::decrease (int u){
   int tdec = u;
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

Unit * TraditionalArmy::split (int num){
   if(num > numUnits())
      num = numUnits();
   this->decrease(num);
   return new TraditionalArmy(whereAt(),num);
}
/// \todo this should throw an exception if an invalid unit was passed.
int TraditionalArmy::merge (Unit * u){
   int n = u->numUnits();
   if (this != u && u->name() == name()) {
      this->increase(n);
      delete u;
   }
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

