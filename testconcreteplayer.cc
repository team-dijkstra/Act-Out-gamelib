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

