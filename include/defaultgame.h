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
 *  DefaultGame class 
 */
#ifndef DEFAULT_GAME_H
#define DEFAULT_GAME_H

#include <vector>
#include <string>
#include "game.h"

namespace game {
   class Player;
}
class GameMap;

/// \todo comment DefaultGame class
class DefaultGame : public Game {
  public:
   /// PlayerName typedef is for clarity and code readability
   typedef Game::PlayerName PlayerName;
   
   typedef Game::playerlist playerlist;

   //constructor
   DefaultGame(GameMap * g);
   //destructor
   ~DefaultGame();
   
   //accessors
   /// \return all the system Players
   playerlist systemPlayers() const;

   /// \return all the regular Players
   playerlist players() const;

   /// \return if the game has winner and who it is
   game::Player* winner() const;

   /// \return the player which has the current turn
   game::Player* currentTurn() const;

   /// \return the GameMap of the current game.
   GameMap* currentGame() const;
   
   //mutators
   /// \param playernames -- all the players playing this game
   //
   /// Performs all operations needed to initialize game state
   void SetupGame(std::vector<PlayerName> playernames);

  private:
   GameMap * gMap;
   playerlist gPlayers;
   playerlist sysPlayers;
};

#endif
