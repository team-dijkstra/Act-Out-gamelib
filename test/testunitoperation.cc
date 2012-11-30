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
/** \file testunitoperation.cc
 * Contains tests for the UnitOperation class and subclasses
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "filterbyunittype.h"
#include "filterbyallunittypes.h"
#include "fk_fakeunit.h"
#include "fk_faketerritory.h"

using namespace game;

/// Class containing the test cases for Default UnitOperation implementations.
/// The implementation is exercised through its interface UnitOperation.
class TestUnitOperation : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestUnitOperation);
   CPPUNIT_TEST(filtername_should_be_as_constructed);
   CPPUNIT_TEST(filter_operator_should_be_return_properly);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different filters used in testing
   UnitOperation * filterAll;
   UnitOperation * filterFakeUnit1;
   UnitOperation * filterFakeUnit2;
   Unit * u1;
   Unit * u2;
   Territory * t;
   
  public:
   /// \cond SETUPTEARDOWNUNITOPERATIONTEST
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
   /// \endcond
   
   /// \test ensure that the filter names are correctly reported
   void filtername_should_be_as_constructed()  {
      CPPUNIT_ASSERT(filterAll->name() == "AllUnits");
      CPPUNIT_ASSERT(filterFakeUnit1->name() == "FakeUnit");
      CPPUNIT_ASSERT(filterFakeUnit2->name() == "Type2");
   }

   /// \test ensure that the filter filters correctly
   void filter_operator_should_be_return_properly()  {
      CPPUNIT_ASSERT((*filterAll)(u1) == true);
      CPPUNIT_ASSERT((*filterAll)(u2) == true);
      
      CPPUNIT_ASSERT((*filterFakeUnit1)(u1) == true);
      CPPUNIT_ASSERT((*filterFakeUnit1)(u2) == false);
      CPPUNIT_ASSERT((*filterFakeUnit2)(u2) == true);
      CPPUNIT_ASSERT((*filterFakeUnit2)(u1) == false);
   }

};

/// \cond TestUnitOperationREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestUnitOperation);
/// \endcond
