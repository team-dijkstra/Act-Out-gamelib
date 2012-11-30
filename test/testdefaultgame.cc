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
#include "defaultgame.h"


/// Class containing the test cases for DefaultGame. The DefaultGame
/// is exercised through its interface Game.
class TestDefaultGame : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestDefaultGame);
   CPPUNIT_TEST(gamename_should_be_as_constructed);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different games used in testing
   Game * gameA;
   Game * gameB;
   GameMap * gmA;
   GameMap * gmB;
   
  public:
   /// \cond SETUPTEARDOWNDEFAULTGAMETEST
   // initialization for the test game
   void setUp() {
      /*
       *cant instantiate these objects until stlgamemap is done
       *
      gmA = new 
      gmB = new
      gameA = new DefaultGame();
      gameB = new DefaultGame();
      */
   }
   // frees memory for the games
   void tearDown() {
      delete gameA;
      delete gameB;
   }
   /// \endcond
   
   /// \test ensure that the game names are correctly reported
   void gamename_should_be_as_constructed()  {
//      CPPUNIT_ASSERT(gameA->name() == "Marshal Forces");
//      CPPUNIT_ASSERT(gameB->name() == "Attack");
   }

};
/// \cond TestDefaultGameREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestDefaultGame);
/// \endcond
