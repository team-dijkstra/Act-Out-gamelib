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
/** \file defaultgame.h
 *  \brief extends Game interface class
 * 
 *  AltDefaultGame class 
 */
#ifndef ALT_DEFAULT_GAME_H
#define ALT_DEFAULT_GAME_H

#include <vector>
#include <string>

#include "player.h"
#include "game.h"
#include "gamemap.h"


/**
 * \class AltDefaultGame
 *
 * Provides an alternate version of the Game interface. This provides a
 * reference implementation with no external dependencies other than the
 * STL. Deletes all phases, all system and regular players, and the game map.
 */
class AltDefaultGame : public Game {
  public:
   
   typedef Game::PlayerName PlayerName; ///< \typedef name of a Player

   typedef Game::playerlist playerlist; ///< \typedef A list of Player objects

   //constructor

   /// sets gMap to NULL
   AltDefaultGame();
   
   /// Destructor. Deletes all phases, all system and regular players,
   /// and the game map.
   ~AltDefaultGame();
   
   //accessors
   /// @copydoc Game::systemPlayers()
   playerlist systemPlayers() const;

   /// @copydoc Game::players()
   playerlist players() const;

   /// @copydoc Game::winner()
   Player* winner() const;

   //return the player which has the current turn
   //Player* currentTurn() const;
   ///
   /// @copydoc Game::currentGame()
   GameMap* currentGame() const;
   
   //mutators
   
   /// @copydoc Game::setupGame()
   void setupGame(std::vector<PlayerName> playernames, std::vector< PlayerName > territoryNames );

  private:
   
   GameMap * gMap;
   playerlist gPlayers;
   playerlist sysPlayers;
   Player::phaselist phases;
   
   //private member function

   /// sets up the game map adjacencies
   /// \param terrList -- list of territories
   void setupGMap(GameMap::TerritoryList terrList);
   
};

#endif
