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
 *  DefaultGame class is experimental.
 */
#ifndef DEFAULT_GAME_H
#define DEFAULT_GAME_H

#include <vector>
#include <string>

#include "player.h"
#include "game.h"
//#include "gamemap.h"
//class Player;
//class GameMap;


/// \todo comment DefaultGame class
class DefaultGame : public Game {
  public:
   
   typedef Game::PlayerName PlayerName; ///<  list of player names
   
   typedef Game::playerlist playerlist; ///<  list of players

   //constructors
   
   // DefaultGame(playerlist pl, GameMap * g = NULL);

   /// \param g -- GameMap object, default to null;
   ///
   /// supplied GameMap is no longer used
   DefaultGame(GameMap * g = NULL);
   
   //destructor
   
   ~DefaultGame();
   
   //accessors
   
   /// @copydoc Game::systemPlayers
   playerlist systemPlayers() const;

   /// @copydoc Game::players
   playerlist players() const;

   /// @copydoc Game::winner
   Player* winner() const;

   // return the player which has the current turn
   //Player* currentTurn() const;

   /// @copydoc Game::currentGame
   GameMap* currentGame() const;
   
   //mutators
   
   /// @copydoc Game::setupGame
   void setupGame(std::vector<PlayerName> playernames, std::vector< PlayerName > territoryNames );

  private:
   
   GameMap * gMap; //! @copydoc AltDefaultGame::gmap
   playerlist gPlayers; //! @copydoc AltDefaultGame::gPlayer
   playerlist sysPlayers; //! @copydoc AltDefaultGame::sysPlayers
   Player::phaselist phases; //! @copydoc AltDefaultGame::phases
   
};

#endif
