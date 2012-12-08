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
/** \file defaultplayer.cc 
 * Implementation file for DefaultPlayer class
 * Detatailed descriptions of each method are in the header file
 */
#include "defaultplayer.h"
#include "action.h"
#include "territoryoperation.h"
#include "game.h"
#include "defaultphase.h"
#include "debug.h"
#include "altgamemap.h"
#include "filterbyallunittypes.h"
#include "territory.h"
#include "config.h"

DefaultPlayer::DefaultPlayer(std::string nm):pName(nm),isAlive(true)
{
   DefaultPhase dp1(phase::MARSHAL);
   DefaultPhase dp2(phase::ATTACK);
   phases.push_back(&dp1);
   phases.push_back(&dp2);
   currentPhase = phases.begin();
   ourGame = NULL;
}

DefaultPlayer::DefaultPlayer(std::string nm, const phaselist & Plist, GameMap * gmp):pName(nm),isAlive(true), phases(Plist), ourGame(gmp)
{
   currentPhase = phases.begin();
}

bool DefaultPlayer::alive(){
   /// \todo this fuction should throw an exception if ourGame is NULL
   // this checks # of territories owned, if zero, return false. call GameMap::(list territories by player method)
   /// \todo need to make sure that alive() does not return false when any of the territories are unclaimed.
   if ( ourGame != NULL && isAlive) //make sure we have gamemap object and are still alive
   {
      AltGameMap::TerritoryList checkT;
      checkT = ourGame->players(this);
      if (checkT.empty() )
	 isAlive = false;
   }
   return isAlive;

}

std::string DefaultPlayer::name() const{
   return pName;
}

DefaultPlayer::phaselist DefaultPlayer::remainingPhases() const{
   phaselist newlist;
   assert(currentPhase != phases.end() );
   phaselist::const_iterator it;
   it = currentPhase;
//   it++;
//   std::copy(it, phases.end(), newlist.begin());
   for( ; it!=phases.end() ; ++it)
   {
      newlist.push_back(*it);
   }
   
   return newlist;
}

Unit::actionContainer DefaultPlayer::actions(TerritoryOperation * op) //const gives errors
{
   Unit::actionContainer ourActions;
   
   /// \todo this fuction should throw an exception if ourGame is NULL
   if ( ourGame != NULL )
   {
      //dout << "entered gamemap" << std::endl;
      //get the territories
      GameMap::TerritoryList territories = ourGame->filter(op);

      //loop through the territories
      
      for ( GameMap::TerritoryList::iterator it = territories.begin(); it != territories.end(); ++it)
      {
	 //loop through all units in territory
	 Territory::unitContainer list_of_units;
	 FilterByAllUnitTypes unitFilter;
	 list_of_units = (*it)->units(&unitFilter);
	 
	 for ( Territory::unitContainer::iterator unIT = list_of_units.begin(); unIT != list_of_units.end(); ++unIT)
	 {
	    //get actions
	    Unit::actionContainer unitsActions =  (*unIT).second->actions();
	    //loop through actions to see what is applicable for the currentPhase
	    //dout << "iterating through unitContainer, before  actionContainer =========================<< unitsActions size is: "<< unitsActions.size() <<std::endl;
	    
	    for ( Unit::actionContainer::iterator acIT = unitsActions.begin(); acIT != unitsActions.end(); ++acIT)
	    {
	       Action * currAction = (*acIT);
	       bool appl = currAction->applicable(*currentPhase);
	       
	       //dout << "iterating through actionContainer, before applicable() == "<< appl << " Action.name(): == "<< (*acIT)->name()
	       //dout << " Action.description(): == "<< (*acIT)->description() << std::endl;
	       if (appl)
	       {
		  //dout << "Inside applicable: " << " Action.name(): == "<< (*acIT)->name() << " Action.description(): == "<< (*acIT)->description() << std::endl;
		  ourActions.push_back( (*acIT) );
	       }
	    }

	 }
	 
      }

      
   }
   return ourActions; // \todo
}

bool DefaultPlayer::nextPhase()
{
   ++currentPhase;
   if(currentPhase == phases.end())
   {
      currentPhase = phases.begin();
      return true;
   }
   return false;

      
}
