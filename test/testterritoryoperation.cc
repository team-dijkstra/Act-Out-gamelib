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
#include "filterbyterritoryowner.h"
#include "landterritory.h"
#include "defaultplayer.h"


/// Class containing the test cases for Default TerritoryOperation implementations.
/// The implementation is exercised through its interface TerritoryOperation.
class TestTerritoryOperation : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestTerritoryOperation);
   CPPUNIT_TEST(filter_operator_should_be_return_properly);
   CPPUNIT_TEST(filter_owner_operator_should_be_return_properly);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // filter used in testing
   TerritoryOperation * filterTerritory;
   TerritoryOperation * filterOwner;
   Territory * t1;
   Territory * t2;
   Player * p1;
   Player * p2;
   
  public:
   /// \cond SETUPTEARDOWNTERRITORYOPERATIONTEST
   // initialization for the test filter
   void setUp() {
      p1 = new DefaultPlayer(std::string("ply1"));
      p2 = new DefaultPlayer(std::string("ply2"));
      std::string a = "terr1";
      t1 = new LandTerritory(a, p1);
      t2 = new LandTerritory("terr2", p2);
      //p1 = t2->owner();
      filterTerritory = new FilterByTerritoryName(t2->name());
      std::string n = t2->owner()->name();
      
      filterOwner = new FilterByTerritoryOwner(n);
   }
   // frees memory for the filters
   void tearDown() {
      delete filterTerritory;
      delete filterOwner;
      delete p1;
      delete p2;
      delete t1;
      delete t2;
   }
   /// \endcond
   
   /// \test ensure that the filter filters correctly
   void filter_operator_should_be_return_properly()  {
      CPPUNIT_ASSERT((*filterTerritory)(t1) == false);
      CPPUNIT_ASSERT((*filterTerritory)(t2) == true);
   }

   /// \test ensure that the filter filters correctly
   void filter_owner_operator_should_be_return_properly()  {
      CPPUNIT_ASSERT((*filterOwner)(t1) == false);
      CPPUNIT_ASSERT((*filterOwner)(t2) == true);
   }
   
};

/// \cond TestTerritoryOperationREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestTerritoryOperation);
/// \endcond
