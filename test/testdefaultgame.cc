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
/** \file testdefaultgame.cc
 * Contains tests for the DefaultGame class
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include "defaultgame.h"
#include "defaultplayer.h"
#include "gamemap.h"



/// Class containing the test cases for DefaultGame. The DefaultGame
/// is exercised through its interface Game.
class TestDefaultGame : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestDefaultGame);
   //CPPUNIT_TEST(gamename_should_be_as_constructed);
   CPPUNIT_TEST(game_players_should_return_playerlist);
   CPPUNIT_TEST(game_systemPlayers_should_return_playerlist);
   CPPUNIT_TEST(game_winner_should_return_unclaimed_unil_winner_found);
   CPPUNIT_TEST(game_currentGame_should_return_GameMap_object);   
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different games used in testing
   Game * gameA;
   // Game * gameB;
   //GameMap * gmA;
   //GameMap * gmB;
   Player * un;
   
  public:
   /// \cond SETUPTEARDOWNDEFAULTGAMETEST
   // initialization for the test game
   void setUp() {
      /*
       *cant instantiate these objects until stlgamemap is done
       *
      gmA = new 
      gmB = new*/
      un = new DefaultPlayer("Undeclared");
      gameA = new DefaultGame();
//      gameB = new DefaultGame();

      //setup Players and game
      std::vector<Game::PlayerName> names, terrNames;
      //players
      Game::PlayerName a = "Tim" , b = "Tom" , c = "Tony";
      names.push_back(a);
      names.push_back(b);
      names.push_back(c);
      //territories
      a = "Bender" ; b = "Fry" ; c = "Hermies";
      names.push_back(a);
      names.push_back(b);
      names.push_back(c);
      gameA->setupGame(names, terrNames);
   }
   // frees memory for the games
   void tearDown() {
      delete gameA;
      //delete gameB;
      delete un;
   }
   /// \endcond
   
   /// \test ensure that the game names are correctly reported
//   void game_setupGgame_should_create_playerlist_and_systemPlayers()  {
//      CPPUNIT_ASSERT(gameA->name() == "Marshal Forces");
//      CPPUNIT_ASSERT(gameB->name() == "Attack");
//   }

   /// \test ensure that the players are correctly reported
   void game_players_should_return_playerlist()  {
      Game::playerlist myPlayers;
      myPlayers = gameA->players();
      CPPUNIT_ASSERT(myPlayers.size() != 0);  

      //check the players are right
      Player * p1;
      p1 = myPlayers[0];
      CPPUNIT_ASSERT(p1->name() == "Tim" );
      p1 = myPlayers[1];
      CPPUNIT_ASSERT(p1->name() == "Tom" );
      p1 = myPlayers[2];
      CPPUNIT_ASSERT(p1->name() == "Tony" );
   }
   
   void game_systemPlayers_should_return_playerlist()  {
      Game::playerlist sysList;
      sysList = gameA->systemPlayers();
      CPPUNIT_ASSERT(sysList.size() != 0);
      Game::playerlist::iterator sysIT;
      sysIT = sysList.begin();
      //check that first player is unclaimed
      Player * sysp1;
      sysp1 = *sysIT;
      //std::cout <<std::endl <<std::endl << sysp1->name() <<std::endl <<std::endl;
      CPPUNIT_ASSERT(sysp1->name() == std::string("Unclaimed"));
   }
   
   /// \test ensure that the winner is correctly reported
   void game_winner_should_return_unclaimed_unil_winner_found()  {
      Player * winner;
      winner = gameA->winner();
      CPPUNIT_ASSERT(winner->name() == "Unclaimed");
      //      CPPUNIT_ASSERT(gameB->winner() == "Undeclared");
   }

   /// \test ensure that the player whose turn it is, is correctly reported
   void game_currentGame_should_return_GameMap_object()  {
      //GameMap * refGame;

      //refGame = gameA->currentGame();

      //CPPUNIT_ASSERT_NO_THROW ??? look in docs
      //CPPUNIT_ASSERT_NO_THROW(refGame->begin());
      
   }
   

};
/// \cond TestDefaultGameREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestDefaultGame);
/// \endcond
