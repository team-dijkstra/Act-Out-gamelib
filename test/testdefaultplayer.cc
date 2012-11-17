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
/** \file testdefaultplayer.cc
 * Contains tests for the DefaultPlayer class
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "defaultplayer.h"
#include "defaultphase.h"

/// Class containing the test cases for DefaultPlayer. The DefaultPlayer
/// is exercised through its interface Player.
class TestPlayer : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestPlayer);
   CPPUNIT_TEST(player_name_should_be_as_constructed);
   CPPUNIT_TEST(player_should_be_alive_when_constructed);
   CPPUNIT_TEST(player_remainingPhases_should_return_a_phaselist);
   CPPUNIT_TEST(player_nextPhases_should_move_to_next_element_in_phaselist);
   
   CPPUNIT_TEST_SUITE_END();
   
  private:
   /// \cond SETUPTEARDOWNPLAYERTEST
   // different players used in testing
   Player * playerA;
   Player * playerB;
   Player::phaselist Plist;
   Player::phaselist::iterator it;
  public:
   // initialization for the test player
   void setUp() {
      Plist.push_back(new DefaultPhase("Marshall"));
      Plist.push_back(new DefaultPhase("Attack"));
      playerA = new DefaultPlayer(std::string("Player1"),Plist);
      playerB = new DefaultPlayer(std::string("Player2"),Plist);
   }
   // frees memory for the players
   void tearDown() {
      delete playerA;
      delete playerB;
   }
   /// \endcond
   
   
   /// \test ensure that the player names are correctly reported
   void player_name_should_be_as_constructed()  {
      CPPUNIT_ASSERT(playerA->name() == "Player1");
      CPPUNIT_ASSERT(playerB->name() == "Player2");
   }

   void player_should_be_alive_when_constructed()
   {
      CPPUNIT_ASSERT(playerA->alive() == true);
      CPPUNIT_ASSERT(playerB->alive() == true);
   }
      

   /// \test checks that phaselist is correctly returned
   void player_remainingPhases_should_return_a_phaselist()
   {
      //CPPUNIT_ASSERT(playerA->alive() == true);
      //CPPUNIT_ASSERT(playerB->alive() == true);
/*      for(it = Plist.begin();it!=Plist.end();it++)
      {
	 
      }
*/
      Player::phaselist Pl2;
      Pl2 = playerA->remainingPhases();
      CPPUNIT_ASSERT(Plist.size() == Pl2.size());
      CPPUNIT_ASSERT(Plist == Pl2);
      CPPUNIT_ASSERT(*(Plist.begin()) == *(Pl2.begin()));
      
   }

   /** \test checks that nextPhase properly sets DefaultPlayer::currentPhase
    *  to the proper next phase
    */
   void player_nextPhases_should_move_to_next_element_in_phaselist()
   {
      it = Plist.begin();
      ++it;
      Player::phaselist Pl2;
      Player::phaselist::iterator it2;
      playerA->nextPhase();
      Pl2 = playerA->remainingPhases();
      it2 = Pl2.begin();
      //CPPUNIT_ASSERT(Plist.size() == Pl2.size());
      //CPPUNIT_ASSERT(Plist == Pl2);
      CPPUNIT_ASSERT(*(it2) == *(it));
            
      playerA->nextPhase();
      Pl2 = playerA->remainingPhases();
      it2 = Pl2.begin();
      it = Plist.begin();
      CPPUNIT_ASSERT(*(it2) == *(it));
   }
};
/// \cond TestPlayerREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestPlayer);
/// \endcond
