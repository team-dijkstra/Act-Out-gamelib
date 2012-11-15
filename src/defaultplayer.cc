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
#include "defaultplayer.h"
#include "action.h"
#include "territoryoperation.h"
#include "game.h"
#include "defaultphase.h"
#include "debug.h"
//#include "phase.h"

DefaultPlayer::DefaultPlayer(std::string nm):pName(nm),isAlive(true)
{
   phases.push_back(new DefaultPhase("Marshall"));
   phases.push_back(new DefaultPhase("Attack"));
   currentPhase = phases.begin();
}

DefaultPlayer::DefaultPlayer(std::string nm, const Player::phaselist & Plist):pName(nm),isAlive(true), phases(Plist)
{
   currentPhase = phases.begin();
}

bool DefaultPlayer::alive() const{
   /// \todo if isAlive, need to have it check # of territories owned if zero, set isAlive to false. call GameMap::(list territories by player method)
   return isAlive;
}

/// \return the name of the player
std::string DefaultPlayer::name() const{
   return pName;
}

/// \return the remaining phases in this players current turn
DefaultPlayer::phaselist DefaultPlayer::remainingPhases() const{
   phaselist newlist;
   assert(currentPhase != phases.end() );
   phaselist::const_iterator it;
   it = currentPhase;
//   it++;
//   std::copy(it, phases.end(), newlist.begin());
   for(it ; it!=phases.end() ; ++it)
   {
      newlist.push_back(*it);
   }
   
   return newlist;
}

/// \return the valid actions that this player can perform given
///         this unitoperation.
Unit::actionContainer DefaultPlayer::actions(TerritoryOperation * op) const
{
   /// \todo implement this
   /// \todo I put this stuff here bcs. I wanted the 'nonvoid function not returning' warnings to shutup
   (void)op; // \todo
   Unit::actionContainer test; // \todo
   return test; // \todo
}

//Mutator
/// \post moves to the next phase, if the last phase is reached
///       reset to the first phase
void DefaultPlayer::nextPhase(){

}
