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
#include "attritionattackaction.h"
#include "defaultphase.h"
#include "buildtraditionalarmyaction.h"
#include "config.h"


 //debugging
#include "debug.h"
#include <iostream>
#include <string>

TraditionalArmy::TraditionalArmy(Territory * t, int nunit ): nUnits(nunit), uTerritory(t), uName("TraditionalArmy")
{
   uActions.push_back(new MoveAction(this));
   uActions.push_back(new AttritionAttackAction(this));
}

///\deprecated no longer use this constructor
TraditionalArmy::TraditionalArmy(Territory * t, int nunit, Unit::actionContainer applicableActions ): nUnits(nunit), uTerritory(t), uName("TraditionalArmy"), uActions(applicableActions)
{
}

TraditionalArmy::~TraditionalArmy(){
   actionContainer::iterator it;
   for(it = uActions.begin(); it != uActions.end(); ++it)
      delete *it;
}

int TraditionalArmy::increase (int u){
   nUnits += u;
   return nUnits;
}

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

// !Dangerous! only for demo, don't have time to refactor Action interface class
//TraditionalArmy specific mutator
// allows us to pass in and set action container to a LandTerritory object
void TraditionalArmy::setActions(Unit::actionContainer acts)
{
   //assert (acts == uActions);
   assert (acts != uActions);
   if(&acts != &uActions)//don't delete ourself
   {
      actionContainer::iterator it;
//debug
      for(it = uActions.begin(); it != uActions.end(); ++it)
      {
	 //debug
//	 std::string s = (*it)->name();
//	 int sz = uActions.size();
//	 std::cout << std::endl <<sz << " <-size,name-> "<< s << std::endl;
	 delete *it; //free memory for actions if not the same
      }
/*
      uActions.clear();
      for(it = acts.begin(); it != acts.end(); ++it)
      {
	 //debug
//	 int sz = uActions.size();
//	 Action * a = (*it);
//	 std::string s = a->name();
//	 std::cout << std::endl << sz << " <-size,name-> "<< s << std::endl;

	 uActions.push_back(a);
	 /*
	 //debugging code:
	   DefaultPhase dp(std::string(phase::MARSHAL));
	 uActions.push_back(new MoveAction(&dp, this));
	 uActions.push_back(new BuildTraditionalArmyAction(&dp, this));
	 uActions.push_back(new AttritionAttackAction(this,&dp));
	 * /

	 }*/

      
   uActions.clear();
   uActions = acts;
   }
   
}
