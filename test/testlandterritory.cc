/*
 * cpsc 2720 - Project - Territory Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "landterritory.h"
#include "concreteplayer.h"


/// Class containing the test cases for LandTerritory. The LandTerritory
/// is exercised through its interface Territory.
class TestTerritory : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestTerritory);
   CPPUNIT_TEST(territoryname_should_be_as_constructed);
   CPPUNIT_TEST(territoryowner_should_be_as_constructed);
   CPPUNIT_TEST_SUITE_END();
   
private:
   // different territorys used in testing
   Territory * territoryA;
   Territory * territoryB;
   Player * ply1;
   Player * ply2;
   
public:
   // initialization for the test territory
   void setUp() {
      ply1 = new ConcretePlayer(std::string("player1"));
      ply2 = new ConcretePlayer(std::string("player2"));
      territoryA = new LandTerritory(std::string("Spain"), ply1);
      territoryB = new LandTerritory(std::string("Canada"), ply2);
   }

   // frees memory for the territorys
   void tearDown() {
      delete territoryA;
      delete territoryB;
      delete ply1;
      delete ply2;
   }

   /// \test ensure that the territory names are correctly reported
   void territoryname_should_be_as_constructed()  {
      //CPPUNIT_ASSERT(territoryA->name() == "Spain");
      //CPPUNIT_ASSERT(territoryB->name() == "Canada");
   }

   /// \test ensure that the territory players are correct
   void territoryowner_should_be_as_constructed()  {
      //CPPUNIT_ASSERT(territoryA->owner() == ply1);
      //CPPUNIT_ASSERT(territoryB->owner() == ply2);
   }

   
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTerritory);

