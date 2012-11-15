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
#ifndef DEFAULT_PLAYER_H
#define DEFAULT_PLAYER_H

#include "player.h"


class Phase;
class Action;
class TerritoryOperation;
class Game;

class DefaultPlayer : public Player {
  public:
//   DefaultPlayer(std::string nm, Game * g);
   DefaultPlayer(std::string nm);
   DefaultPlayer(std::string nm, const Player::phaselist & Plist);
   ~DefaultPlayer() {}
   //accessors
   /// \return true if the player is alive (i.e. still in the
   ///         game, false otherwise
   bool alive() const;

   /// \return the name of the player
   std::string name() const;

   /// \return the remaining phases in this players current turn
   phaselist remainingPhases() const;

   /// \return the valid actions that this player can perform given
   ///         this unitoperation.
   Unit::actionContainer actions(TerritoryOperation * op) const;

   //Mutator
   /// \post moves to the next phase, it the last phase is reached
   ///       reset to the first phase
   void nextPhase();

  private:
   typedef Player::phaselist phaselist;
  
   std::string pName;
   bool isAlive;
   phaselist phases;
   phaselist::const_iterator currentPhase;
   
};

#endif
