/*
 * cpsc 2720 - Project - Filter Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "filterbyunittype.h"
#include "filterbyallunittypes.h"
#include "fk_fakeunit.h"
#include "fk_faketerritory.h"


/// Class containing the test cases for ConcreteFilter. The ConcreteFilter
/// is exercised through its interface Filter.
class TestFilter : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestFilter);
   CPPUNIT_TEST(filtername_should_be_as_constructed);
   CPPUNIT_TEST(filter_operator_should_be_return_properly);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different filters used in testing
   Filter * filterAll;
   Filter * filterFakeUnit1;
   Filter * filterFakeUnit2;
   Unit * u1;
   Unit * u2;
   Territory * t;
   
  public:
   // initialization for the test filter
   void setUp() {
      std::string a = "terr1";
      t = new FakeTerritory(a);
      u1 = new FakeUnit(1,t);
      u2 = new FakeUnit(2,t,"Type2");
      filterAll = new FilterByAllUnitTypes(u1);
      filterFakeUnit1 = new FilterByUnitType(u1);
      filterFakeUnit2 = new FilterByUnitType(u2);
   }

   // frees memory for the filters
   void tearDown() {
      delete filterAll;
      delete filterFakeUnit1;
      delete filterFakeUnit2;
      delete u1;
      delete u2;
      delete t;
   }

   /// \test ensure that the filter names are correctly reported
   void filtername_should_be_as_constructed()  {
      CPPUNIT_ASSERT(filterAll->name() == "AllUnits");
      CPPUNIT_ASSERT(filterFakeUnit1->name() == "FakeUnit");
      CPPUNIT_ASSERT(filterFakeUnit2->name() == "Type2");
   }

   void filter_operator_should_be_return_properly()  {
      CPPUNIT_ASSERT((*filterAll)(u1) == true);
      CPPUNIT_ASSERT((*filterAll)(u2) == true);
      
      CPPUNIT_ASSERT((*filterFakeUnit1)(u1) == true);
      CPPUNIT_ASSERT((*filterFakeUnit1)(u2) == false);
      CPPUNIT_ASSERT((*filterFakeUnit2)(u2) == true);
      CPPUNIT_ASSERT((*filterFakeUnit2)(u1) == false);
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFilter);

