/*
 * cpsc 2720 - Project - FakeUnit Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "fakeunit.h"
#include "faketerritory.h"


/// Class containing the test cases for ConcreteFakeUnit. The ConcreteFakeUnit
/// is exercised through its interface FakeUnit.
class TestFakeUnit : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestFakeUnit);
   CPPUNIT_TEST(fakeTerritoryName_should_be_as_constructed);
   CPPUNIT_TEST(fakeUnitname_should_be_as_constructed);
   CPPUNIT_TEST(fakeUnit_numUnits_should_be_as_constructed);
   CPPUNIT_TEST(fakeUnit_increase_should_return_properly);
   CPPUNIT_TEST(fakeUnit_decrease_should_return_properly);
   CPPUNIT_TEST(fakeUnit_whereAt_should_return_its_territory_properly);
   CPPUNIT_TEST_SUITE_END();
   
private:
   // different fakeUnits used in testing
   Unit * fakeUnitA;
   Unit * fakeUnitB;
   Unit * fakeUnitC;
   Territory * t1;
   Territory * t2;

   
public:
   // initialization for the test fakeUnit
   void setUp() {
      std::string a,b;
      a = "terr1";
      b = "terr2";
      t1 = new FakeTerritory(a);
      t2 = new FakeTerritory(b);
      
      fakeUnitA = new FakeUnit(1, t1);
      fakeUnitB = new FakeUnit(2, t2);
      fakeUnitC = new FakeUnit(10, t2);

   }

   // frees memory for the fakeUnits
   void tearDown() {
      delete fakeUnitA;
      delete fakeUnitB;
   }

   /// \test ensure that the fakeUnit names are correctly reported
   void fakeTerritoryName_should_be_as_constructed()  {
      CPPUNIT_ASSERT(t1->name() == "terr1");
      CPPUNIT_ASSERT(t2->name() == "terr2");
   }
   
   void fakeUnitname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(fakeUnitA->name() == "FakeUnit");
      CPPUNIT_ASSERT(fakeUnitB->name() == "FakeUnit");
   }

   void fakeUnit_numUnits_should_be_as_constructed()  {
      CPPUNIT_ASSERT(fakeUnitA->numUnits() == 1);
      CPPUNIT_ASSERT(fakeUnitB->numUnits() == 2);
   }

   void fakeUnit_increase_should_return_properly()  {
      fakeUnitA->increase(fakeUnitB);
      fakeUnitC->increase(fakeUnitA);
      
      CPPUNIT_ASSERT(fakeUnitA->numUnits() == 3);
      CPPUNIT_ASSERT(fakeUnitB->numUnits() == 2);
      CPPUNIT_ASSERT(fakeUnitC->numUnits() == 13);
   }

   void fakeUnit_decrease_should_return_properly()  {
      fakeUnitB->decrease(fakeUnitA);
      fakeUnitA->decrease(fakeUnitC);
      
      CPPUNIT_ASSERT(fakeUnitA->numUnits() == 0);
      CPPUNIT_ASSERT(fakeUnitB->numUnits() == 1);
      CPPUNIT_ASSERT(fakeUnitC->numUnits() == 10);
   }

   void fakeUnit_whereAt_should_return_its_territory_properly()  {
      CPPUNIT_ASSERT(fakeUnitA->whereAt() == t1);
      CPPUNIT_ASSERT(fakeUnitB->whereAt() == t2);
      CPPUNIT_ASSERT(fakeUnitC->whereAt() == t2);
   }
   
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFakeUnit);

