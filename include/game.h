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
/** \file
 *  \brief Interface file for game class -- game.h
 * 
 *  Game Interface class 
 */
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

class Player;
class GameMap;

/// Game Interface class specifies the bahavior of the game object
class Game {
  public:


   typedef std::string PlayerName; ///<  string to be names of players

   typedef std::vector<Player*> playerlist; ///<  vector of pointers to Players

   /// Virtual base destructor
   virtual ~Game() {}

   //accessors
   
   /// \return all the system Players
   virtual playerlist systemPlayers() const =0;

   /// checks if there is a winner and if there is not, then the player
   /// 'unclaimed' is the winner.
   /// \return the winner
   virtual playerlist players() const =0;

   /// \return the GameMap of the current game.
   virtual Player* winner() const =0;

   // return the player which has the current turn
   //virtual Player* currentTurn() const =0;

   /// \return the GameMap of the current game.
   virtual GameMap* currentGame() const =0;
   
   //mutators

   /// Performs all operations needed to initialize game state
   /// \param playernames -- list of strings to be names of players
   /// \param territoryNames -- list of strings to be names of territories
   virtual void setupGame(std::vector<PlayerName> playernames, std::vector< PlayerName > territoryNames) =0;
   
};

#endif
