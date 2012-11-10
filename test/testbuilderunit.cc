/*
 * cpsc 2720 - Project - Unit Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "builderunit.h"
#include "concreteplayer.h"
#include "landterritory.h"


/// Class containing the test cases for BuilderUnit. The BuilderUnit
/// is exercised through its interface Unit.
class TestUnit : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestUnit);
   CPPUNIT_TEST(unitname_should_be_as_constructed);
   CPPUNIT_TEST(unit_whereAt_should_be_as_constructed);
   CPPUNIT_TEST(unit_numUnits_should_be_as_constructed);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different units used in testing
   Unit * unitA;
   Unit * unitB;
   Territory * t1;
   Territory * t2;
   Player * p1;
   Player * p2;
   
  public:
   // initialization for the test unit
   void setUp() {
      delete unitA;
      delete unitB;
      p1 = new ConcretePlayer(std::string("player1"));
      p2 = new ConcretePlayer(std::string("player2"));
      t1 = new LandTerritory(std::string("Spain"),p1);
      t2 = new LandTerritory(std::string("Canada"),p2);
      unitA = new BuilderUnit(t1, 1);
      unitB = new BuilderUnit(t2,3);
   }

   // frees memory for the units
   void tearDown() {
      delete unitA;
      delete unitB;
      delete t1;
      delete t2;
      delete p1;
      delete p2;
   }

   /// \test ensure that the unit names are correctly reported
   void unitname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(unitA->name() == "BuilderUnit");
      CPPUNIT_ASSERT(unitB->name() == "BuilderUnit");
   }

   /// \test ensure that the unit locations are correctly reported
   ///       on construction
   void unit_whereAt_should_be_as_constructed()  {
      CPPUNIT_ASSERT(unitA->whereAt() == t1);
      CPPUNIT_ASSERT(unitB->whereAt() == t2);
   }

      /// \test ensure that the unit names are correctly reported
   void unit_numUnits_should_be_as_constructed()  {
      CPPUNIT_ASSERT(unitA->numUnits() == 1);
      CPPUNIT_ASSERT(unitB->numUnits() == 3);
   }
   
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestUnit);

