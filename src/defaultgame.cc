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
#include "defaultplayer.h"
#include "landterritory.h"

//DefaultGame::DefaultGame(playerlist pl, GameMap * g): gPlayers(pl), gMap(g){}
DefaultGame::DefaultGame(GameMap * g):gMap(g){}

DefaultGame::~DefaultGame()
{
   //sysPlayers//gPlayers//
   playerlist::iterator it;
   for(it = gPlayers.begin(); it != gPlayers.end(); ++it)
      delete *it;
   for(it = sysPlayers.begin(); it != sysPlayers.end(); ++it)
      delete *it;
   delete gMap;
   
}

DefaultGame::playerlist DefaultGame::systemPlayers() const{
   return sysPlayers;
}

/// \return all the regular Players
DefaultGame::playerlist DefaultGame::players() const{
   return gPlayers;
}

/// \return if the game has winner and who it is
// cppcheck-suppress unusedFunction 
Player* DefaultGame::winner() const{

   /// \todo fix to return the actual winner
   return sysPlayers[0];
}

// /// \return the player which has the current turn
// cppcheck-suppress unusedFunction
/*Player* DefaultGame::currentTurn() const
{
   return cTurn;
   }*/

/// \return the GameMap of the current game.
// cppcheck-suppress unusedFunction
GameMap* DefaultGame::currentGame() const{
   return gMap;
}
   
//mutators
/// \param playerlist -- all the players playing this game
//
/// performs all operations needed to initialize game state
void DefaultGame::setupGame( std::vector< PlayerName > playernames,std::vector< PlayerName > territoryNames)
{
   //create system players
   Player * sysp = new DefaultPlayer(std::string("Unclaimed"));
   sysPlayers.push_back(sysp);

   //create game players
   std::vector< PlayerName >::iterator it;
   for (it = playernames.begin();it != playernames.end(); ++it)
   {
      std::string name = *it;
      Player * p = new DefaultPlayer(name);
      gPlayers.push_back(p);
   }

   //create the territories
   std::vector<Territory *> terrList;
   for (it = territoryNames.begin();it != territoryNames.end(); ++it)
   {
      std::string name = *it;
      Territory * t = new LandTerritory(name);
      t->owner(sysp); // set owner to unclaimed
      terrList.push_back(t);
   }

   /// \todo make territory adjacencies random
   int count = 0;
   // make the adjacencies
   std::vector<Territory *>::iterator itTr1, itTr2;
   
   for (itTr1 = terrList.begin(); itTr1 != terrList.end(); ++itTr1)
      for (itTr2 = terrList.begin(); itTr2 != terrList.end(); ++itTr2)
      {
	 if(count%2 == 0 && itTr1 != itTr2) //check that a territory is not adjacent to itself
	 {
	    // \todo add to adjacency list
	 }
	 ++count;
      }
}
