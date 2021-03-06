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
/** \file fk_testfakeunit.cc
 * Contains tests for 'Fake' test classes
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "fk_fakeunit.h"
#include "fk_faketerritory.h"


/// Class containing the test cases for DefaultFakeUnit. The DefaultFakeUnit
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
   /// \cond SETUPTEARDOWNFAKETERRITORYTEST
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
      delete fakeUnitC;
      delete t1;
      delete t2;
      
   }
   /// \endcond

   /// \test ensure that the FakeTerritory names are correctly constructed
   void fakeTerritoryName_should_be_as_constructed()  {
      CPPUNIT_ASSERT(t1->name() == "terr1");
      CPPUNIT_ASSERT(t2->name() == "terr2");
   }

   /// \test ensure that the FakeUnit names are correctly constructed
   void fakeUnitname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(fakeUnitA->name() == "FakeUnit");
      CPPUNIT_ASSERT(fakeUnitB->name() == "FakeUnit");
   }

   /// \test ensure that the FakeUnit names are correctly constructed
   void fakeUnit_numUnits_should_be_as_constructed()  {
      CPPUNIT_ASSERT(fakeUnitA->numUnits() == 1);
      CPPUNIT_ASSERT(fakeUnitB->numUnits() == 2);
   }

   /// \test ensure that FakeUnit::increase() works properly
   void fakeUnit_increase_should_return_properly()  {
      fakeUnitA->increase(fakeUnitB->numUnits());
      fakeUnitC->increase(fakeUnitA->numUnits());
      
      CPPUNIT_ASSERT(fakeUnitA->numUnits() == 3);
      CPPUNIT_ASSERT(fakeUnitB->numUnits() == 2);
      CPPUNIT_ASSERT(fakeUnitC->numUnits() == 13);
   }

   /// \test ensure that FakeUnit::decrease() works properly
   void fakeUnit_decrease_should_return_properly()  {
      fakeUnitB->decrease(fakeUnitA->numUnits());
      fakeUnitA->decrease(fakeUnitC->numUnits());
      
      CPPUNIT_ASSERT(fakeUnitA->numUnits() == 0);
      CPPUNIT_ASSERT(fakeUnitB->numUnits() == 1);
      CPPUNIT_ASSERT(fakeUnitC->numUnits() == 10);
   }

   /// \test ensure that FakeUnit::whereAt() works properly
   void fakeUnit_whereAt_should_return_its_territory_properly()  {
      CPPUNIT_ASSERT(fakeUnitA->whereAt() == t1);
      CPPUNIT_ASSERT(fakeUnitB->whereAt() == t2);
      CPPUNIT_ASSERT(fakeUnitC->whereAt() == t2);
   }
   
};

/// \cond TestFakeUnitREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestFakeUnit);
/// \endcond
