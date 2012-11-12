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
#include "phase.h"
#include "territoryoperation.h"
#include "game.h"

DefaultPlayer::DefaultPlayer(std::string nm):pName(nm),isAlive(true)
{}

bool DefaultPlayer::alive() const{
   return isAlive;
}

/// \return the name of the player
std::string DefaultPlayer::name() const{
   return pName;
}

/// \return the remaining phases in this players current turn
std::vector<Phase*> DefaultPlayer::remainingPhases() const{}

/// \return the valid actions that this player can perform given
///         this unitoperation.
std::vector<Action*> DefaultPlayer::validActions(TerritoryOperation * op) const{}

//Mutator
/// \post moves to the next phase, if the last phase is reached
///       reset to the first phase
void DefaultPlayer::nextPhase(){}
