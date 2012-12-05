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
#include <algorithm>
#include "altdefaultgame.h"
#include "altgamemap.h"
#include "defaultplayer.h"
#include "landterritory.h"

//AltDefaultGame::AltDefaultGame(playerlist pl, GameMap * g): gPlayers(pl), gMap(g){}
AltDefaultGame::AltDefaultGame()
{
   gMap = NULL;
}

AltDefaultGame::~AltDefaultGame()
{
   //sysPlayers//gPlayers//
   playerlist::iterator it;
   for(it = gPlayers.begin(); it != gPlayers.end(); ++it)
      delete *it;
   for(it = sysPlayers.begin(); it != sysPlayers.end(); ++it)
      delete *it;
   delete gMap;
   
}

AltDefaultGame::playerlist AltDefaultGame::systemPlayers() const{
   return sysPlayers;
}

/// \return all the regular Players
AltDefaultGame::playerlist AltDefaultGame::players() const{
   return gPlayers;
}

/// \return if the game has winner and who it is
// cpp check -suppress unusedFunction 
Player* AltDefaultGame::winner() const{

   Player * winner = sysPlayers[0];
   Player * lastplayer = winner;

   int players_alive = 0;

   for (playerlist::const_iterator it = gPlayers.begin(); it != gPlayers.end(); ++it)
   {
      bool isAlive = (*it)->alive();
      if(isAlive)
      {
	 lastplayer = *it;
	 ++players_alive;
      }
   }

   if (players_alive == 1)
      winner = lastplayer;
      
   return winner;
}

// /// \return the player which has the current turn
// cppcheck-suppress unusedFunction
/*Player* AltDefaultGame::currentTurn() const
{
   return cTurn;
   }*/

/// \return the GameMap of the current game.
// cppcheck-suppress unusedFunction
GameMap* AltDefaultGame::currentGame() const{
   return gMap;
}
   
//mutators
/// \param playerlist -- all the players playing this game
//
/// performs all operations needed to initialize game state
void AltDefaultGame::setupGame( std::vector< PlayerName > playernames,std::vector< PlayerName > territoryNames)
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
   GameMap::TerritoryList terrList;
   for (it = territoryNames.begin();it != territoryNames.end(); ++it)
   {
      std::string name = *it;
      Territory * t = new LandTerritory(name,sysp);
      //t->owner(sysp); // set owner to unclaimed // not needed
      terrList.push_back(t);
   }

   setupGMap(terrList);
   
}

void AltDefaultGame::setupGMap(GameMap::TerritoryList terrList)
{
   int sz = terrList.size();
   /// \todo make territory adjacencies random
   int count = 0;
   // make the adjacencies
   GameMap::TerritoryList::iterator itTr1;
   AltGameMap::m_adjList ajacency_container;

   //initialize the m_adjList
   for (itTr1 = terrList.begin(); itTr1 != terrList.end(); ++itTr1)
   {
      GameMap::TerritoryList createdAdjList;
      ajacency_container[*itTr1] = createdAdjList;
   }

   AltGameMap::m_adjList::iterator itM, itM2;
   for (itM = ajacency_container.begin(); itM != ajacency_container.end(); ++itM)
   {
      for (itM2 = ajacency_container.begin(); itM2 != ajacency_container.end(); ++itM2)
      {
	 if(count%(sz+1) == 1 && itM != itM2 )
	 {
	    //check to see if each territory is already in the other's adjacency list
	    GameMap::TerritoryList::iterator Mpointer1, Mpointer2;
	    Mpointer1 = find( itM->second.begin(),itM->second.end(), itM2->first );
	    Mpointer2 = find( itM2->second.begin(),itM2->second.end(), itM->first );

	    //if neither territory is in the other list add both to the list
	    if ( ( Mpointer1 ==  itM->second.end() ) && ( Mpointer2 == itM2->second.end() ))
	    {
	       itM->second.push_back(itM2->first);
	       itM2->second.push_back(itM->first);
	    }
	 }
	 ++count;
      }
   }
   gMap = new AltGameMap(ajacency_container);
}
