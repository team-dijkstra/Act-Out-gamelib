/*
 * cpsc 2720 - Project - FakeUnit Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "concretefakeUnit.h"


/// Class containing the test cases for ConcreteFakeUnit. The ConcreteFakeUnit
/// is exercised through its interface FakeUnit.
class TestFakeUnit : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestFakeUnit);
   CPPUNIT_TEST(fakeUnitname_should_be_as_constructed);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different fakeUnits used in testing
   FakeUnit * fakeUnitA;
   FakeUnit * fakeUnitB;

   
  public:
   // initialization for the test fakeUnit
   void setUp() {
      fakeUnitA = new ConcreteFakeUnit(1, std::string("Marshal Forces"));
      fakeUnitB = new ConcreteFakeUnit(std::string("Attack"));
   }

   // frees memory for the fakeUnits
   void tearDown() {
      delete fakeUnitA;
      delete fakeUnitB;
   }

   /// \test ensure that the fakeUnit names are correctly reported
   void fakeUnitname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(fakeUnitA->name() == "Marshal Forces");
      CPPUNIT_ASSERT(fakeUnitB->name() == "Attack");
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFakeUnit);

