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
/*
 * cpsc 2720 - Project - Player Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "concreteplayer.h"


/// Class containing the test cases for ConcretePlayer. The ConcretePlayer
/// is exercised through its interface Player.
class TestPlayer : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestPlayer);
   CPPUNIT_TEST(playername_should_be_as_constructed);
   CPPUNIT_TEST(playername_should_be_alive_when_constructed);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different players used in testing
   Player * playerA;
   Player * playerB;
   
  public:
   // initialization for the test player
   void setUp() {
      playerA = new ConcretePlayer(std::string("Player1"));
      playerB = new ConcretePlayer(std::string("Player2"));
   }

   // frees memory for the players
   void tearDown() {
      delete playerA;
      delete playerB;
   }

   /// \test ensure that the player names are correctly reported
   void playername_should_be_as_constructed()  {
      CPPUNIT_ASSERT(playerA->name() == "Player1");
      CPPUNIT_ASSERT(playerB->name() == "Player2");
   }

     /// \test ensure that the player names are correctly reported
   void playername_should_be_alive_when_constructed()  {
      CPPUNIT_ASSERT(playerA->alive() == true);
      CPPUNIT_ASSERT(playerB->alive() == true);
   }


};

CPPUNIT_TEST_SUITE_REGISTRATION(TestPlayer);

