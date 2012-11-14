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


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "traditionalarmy.h"
#include "landterritory.h"
#include "defaultplayer.h"


/// Class containing the test cases for TraditionalArmyUnit. The TraditionalArmyUnit
/// is exercised through its interface Unit.
class TestUnit : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestUnit);
   CPPUNIT_TEST(unitname_should_be_as_constructed);
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
   void unitname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(unitA->name() == "TraditionalArmy");
      CPPUNIT_ASSERT(unitB->name() == "TraditionalArmy");
   }

   

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestUnit);

