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
/** \file testterritoryoperation.cc
 * Contains tests for the TerritoryOperation class and subclasses
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "filterbyterritoryname.h"
#include "landterritory.h"


/// Class containing the test cases for Default TerritoryOperation implementations.
/// The implementation is exercised through its interface TerritoryOperation.
class TestTerritoryOperation : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestTerritoryOperation);
   CPPUNIT_TEST(filter_operator_should_be_return_properly);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // filter used in testing
   TerritoryOperation * filterTerritory;
   Territory * t1;
   Territory * t2;
   
  public:
   /// \cond SETUPTEARDOWNTERRITORYOPERATIONTEST
   // initialization for the test filter
   void setUp() {
      std::string a = "terr1";
      t1 = new LandTerritory(a);
      t2 = new LandTerritory("terr2");
      filterTerritory = new FilterByTerritoryName(t2->name());
   }
   // frees memory for the filters
   void tearDown() {
      delete filterTerritory;
      delete t1;
      delete t2;
   }
   /// \endcond
   
   /// \test ensure that the filter filters correctly
   void filter_operator_should_be_return_properly()  {
      CPPUNIT_ASSERT((*filterTerritory)(t1) == false);
      CPPUNIT_ASSERT((*filterTerritory)(t2) == true);
   }

};

/// \cond TestTerritoryOperationREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestTerritoryOperation);
/// \endcond
