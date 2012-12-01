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
#include "defaultgame.h"

DefaultGame::DefaultGame(GameMap * g):gMap(g){}

DefaultGame::~DefaultGame()
{
   //sysPlayers//gPlayers//
   playerlist::iterator it;
   for(it = gPlayers.begin(); it != gPlayers.end(); ++it)
      delete *it;
   for(it = sysPlayers.begin(); it != sysPlayers.end(); ++it)
      delete *it;
   
}

DefaultGame::playerlist DefaultGame::systemPlayers() const{}

/// \return all the regular Players
DefaultGame::playerlist DefaultGame::players() const{}

/// \return if the game has winner and who it is
// cppcheck-suppress unusedFunction 
Player* DefaultGame::winner() const{}

/// \return the player which has the current turn
// cppcheck-suppress unusedFunction
/*Player* DefaultGame::currentTurn() const
{
   return cTurn;
   }*/

/// \return the GameMap of the current game.
// cppcheck-suppress unusedFunction
GameMap* DefaultGame::currentGame() const{}
   
//mutators
/// \param playerlist -- all the players playing this game
//
/// performs all operations needed to initialize game state
void DefaultGame::SetupGame( std::vector< PlayerName > playernames ){}
