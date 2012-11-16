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

   //destructor

   virtual ~Player() {}
   
   //accessors
   
   /// \return true if Player is alive (i.e. still in the game, false otherwise
   virtual bool alive() const =0;

   /// \return name of Player
   virtual std::string name() const =0;

   /// \return remaining phases in this Player's current turn
   virtual phaselist remainingPhases() const =0;

   /// \param op -- pointer to a TerritoryOperation that filters out
   ///              unapplicable actions
   /// \return valid actions this Player can perform given this UnitOperation
   virtual Unit::actionContainer actions(TerritoryOperation * op) const =0;

   //mutators
   
   /// \post moves to next phase, if the last phase is reached, reset to first
   ///       phase
   virtual bool nextPhase() =0;
};

#endif
