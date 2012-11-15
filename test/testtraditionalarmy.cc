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
/*
 * cpsc 2720 - Project - Unit Test cases
 */

#include <cassert>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "traditionalarmy.h"
#include "landterritory.h"
#include "defaultplayer.h"
#include "action.h"


/// Class containing the test cases for TraditionalArmyUnit. The TraditionalArmyUnit
/// is exercised through its interface Unit.
class TestTraditionalArmy : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestTraditionalArmy);
   CPPUNIT_TEST(traditionalarmy_name_should_be_as_constructed);
   CPPUNIT_TEST(traditionalarmy_whereAt_should_be_as_constructed);
   CPPUNIT_TEST(traditionalarmy_numUnits_should_be_as_constructed);
   CPPUNIT_TEST(traditionalarmy_increase_should_increment_called_unit);
   CPPUNIT_TEST(traditionalarmy_decrease_should_decrement_numUnit_but_not_below_zero);
   CPPUNIT_TEST(traditionalarmy_actions_should_return_actionContainer);
   CPPUNIT_TEST(traditionalarmy_should_split_correctly);
   CPPUNIT_TEST(traditionalarmy_should_merge_correctly);
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
   /// \cond SETUPTEARDOWNTRADITIONALARMY
   // initialization for the test unit
   void setUp() {
      p1 = new DefaultPlayer(std::string("player1"));
      p2 = new DefaultPlayer(std::string("player2"));
      t1 = new LandTerritory(std::string("Spain"),p1);
      t2 = new LandTerritory(std::string("Italy"),p2);
      unitA = new TraditionalArmy(t1);
      unitB = new TraditionalArmy(t2,4);
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
   /// \endcond

   /// \test ensure that the unit names are correctly reported
   void traditionalarmy_name_should_be_as_constructed()  {
      CPPUNIT_ASSERT(unitA->name() == "TraditionalArmy");
      CPPUNIT_ASSERT(unitB->name() == "TraditionalArmy");
   }

   
   /// \test ensure that the unit locations are correctly reported
   ///       on construction
   void traditionalarmy_whereAt_should_be_as_constructed()  {
      CPPUNIT_ASSERT(unitA->whereAt() == t1);
      CPPUNIT_ASSERT(unitB->whereAt() == t2);
   }

   /// \test ensure that the unit names are correctly reported
   void traditionalarmy_numUnits_should_be_as_constructed()  {
      CPPUNIT_ASSERT(unitA->numUnits() == 1);
      CPPUNIT_ASSERT(unitB->numUnits() == 4);
   }

   /// \test ensure that the increase method works properly
   void traditionalarmy_increase_should_increment_called_unit()  {
      unitA->increase(unitB->numUnits());
      
      CPPUNIT_ASSERT(unitA->numUnits() == 5);
      CPPUNIT_ASSERT(unitB->numUnits() == 4);
   }
   
   /// \test ensure that the decrease method works properly
   void traditionalarmy_decrease_should_decrement_numUnit_but_not_below_zero()
   {
      unitB->decrease(unitA->numUnits());
      CPPUNIT_ASSERT(unitB->numUnits() == 3);

      unitA->decrease(unitB->numUnits());
      CPPUNIT_ASSERT(unitA->numUnits() == 0);

   }
   
   
   /// \test ensure that actions() returns actions container
   void traditionalarmy_actions_should_return_actionContainer()
   {
      Unit::actionContainer a;
      a = unitA->actions();
      CPPUNIT_ASSERT(a.size() != 0);
      CPPUNIT_ASSERT(a[0]->name() == "MoveAction");

   }

   
   /// \test ensure that split(num) splits a unit and preseves quantity
   void traditionalarmy_should_split_correctly()
   {
      Unit * unitC;
      Unit * unitD;
      unitC = unitA->split();
      unitD = unitB->split(3);
      CPPUNIT_ASSERT(unitA->numUnits() == 0);
      CPPUNIT_ASSERT(unitB->numUnits() == 1);
      CPPUNIT_ASSERT(unitC->numUnits() == 1);
      CPPUNIT_ASSERT(unitD->numUnits() == 3);
      unitD = unitB->split(8);
      CPPUNIT_ASSERT(unitB->numUnits() == 0);
      CPPUNIT_ASSERT(unitD->numUnits() == 1);
      delete unitC;
      delete unitD;
   }

   /// \test ensure that merge(u) merges two units and preseves quantity
   void traditionalarmy_should_merge_correctly()
   {
      unitA->merge(unitB->split(4));
      CPPUNIT_ASSERT(unitA->numUnits() == 5);
      CPPUNIT_ASSERT(unitB->numUnits() == 0);
      //CPPUNIT_ASSERT(unitB == NULL);
   }
   
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTraditionalArmy);

