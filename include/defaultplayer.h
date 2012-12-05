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
/** \file defaultplayer.h
 * Implementation file for DefaultPlayer class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef DEFAULT_PLAYER_H
#define DEFAULT_PLAYER_H

#include "player.h"


class Phase;
class Action;
class TerritoryOperation;
class Game;
class GameMap;

/**
 * Implements the Player interface class.
 */
class DefaultPlayer : public Player {
  public:

   //constructors

   /// \param nm -- string, to be name of Player
   //
   /// \post MIL:
   ///       <br>- sets pName to nm
   ///       <br>- sets isAlive to true
   ///       <br>adds each Phase to phases, sets currentPhase to first Phase
   DefaultPlayer(std::string nm);

   /// \param nm -- string, to be name of Player
   /// \param Plist -- phaselist of all Phases
   //
   /// \post MIL:
   ///       <br>- sets pName to nm
   ///       <br>- sets isAlive to true
   ///       <br>- sets phases to Plist
   ///       <br>sets currentPhase to first Phase
   DefaultPlayer(std::string nm, const phaselist & Plist, GameMap * gmp = NULL );

   /// Destructor
   ~DefaultPlayer() {}
   
   //accessors
   
   //! @copydoc Player::alive()
   bool alive();

   //! @copydoc Player::name()
   std::string name() const;

   //! @copydoc Player::remainingPhases()
   phaselist remainingPhases() const;

   //! @copydoc Player::actions()
   Unit::actionContainer actions(TerritoryOperation * op) ;//const; gives problems

   //mutators
   
   //! @copydoc Player::nextPhase()
   bool nextPhase();

  private:
   /// The container type used to hold the list of phases.
   /// \see Player::phaselist.
   typedef Player::phaselist phaselist;
  
   std::string pName; ///< string, name of Player
   bool isAlive; ///< bool, whether Player is alive or dead
   phaselist phases; ///< phaselist of all Phases
   phaselist::const_iterator currentPhase; ///< stores iterator to current Phase
   GameMap * ourGame;
   
};

#endif
