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
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different filters used in testing
   Filter * filterAll;
   Filter * filterFakeUnit;
   Unit * u1;
   Unit * u2;
   Territory * t;
   
  public:
   // initialization for the test filter
   void setUp() {
      std::string a = "terr1";
      t = new FakeTerritory(a);
      u1 = new FakeUnit(1,t);
      u2 = new FakeUnit(2,t);
      filterAll = new FilterByAllUnitTypes(u1);
      filterFakeUnit = new FilterByUnitType(u2);
   }

   // frees memory for the filters
   void tearDown() {
      delete filterAll;
      delete filterFakeUnit;
      delete u1;
      delete u2;
      delete t;
   }

   /// \test ensure that the filter names are correctly reported
   void filtername_should_be_as_constructed()  {
      CPPUNIT_ASSERT(filterAll->name() == "AllUnits");
      CPPUNIT_ASSERT(filterFakeUnit->name() == "FakeUnit");
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFilter);

