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
/// \brief Interface file for Player class -- player.h
//
/// Player Interface Class

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "unit.h"

class Phase;
class Action;
class TerritoryOperation;

/// Player Interface Class specified the Player Behaviours
class Player {
  public:
   typedef std::vector<Phase*> phaselist;
   //accessors
   /// \return true if the player is alive (i.e. still in the
   ///         game, false otherwise
   virtual bool alive() const =0;

   /// \return the name of the player
   virtual std::string name() const =0;

   /// \return the remaining phases in this players current turn
   virtual std::vector<Phase*> remainingPhases() const =0;

   /// \return the valid actions that this player can perform given
   ///         this unitoperation.
   virtual Unit::actionContainer actions(TerritoryOperation * op) const =0;

   //Mutator
   /// \post moves to the next phase, it the last phase is reached
   ///       reset to the first phase
   virtual bool nextPhase() =0;
   
   virtual ~Player() {}
};

#endif
