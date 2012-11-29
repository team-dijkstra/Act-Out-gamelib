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
/** \file testbuildtraditionalarmyaction.cc
 * Contains tests for the BuildTraditionalArmyAction class
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "buildtraditionalarmyaction.h"
#include "defaultphase.h"
#include "landterritory.h"
#include "filterbyallunittypes.h"
#include "traditionalarmy.h"
#include "builderunit.h"

/// Class containing the test cases for BuildTraditionalArmyAction. The BuildTraditionalArmyAction
/// is exercised through its interface Action.
class TestBuildTraditionalArmyAction : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestBuildTraditionalArmyAction);
   CPPUNIT_TEST(actionname_should_be_as_constructed);
   CPPUNIT_TEST(actionphase_should_be_as_constructed);
   CPPUNIT_TEST(action_doaction_should_properly_add_units_to_territory);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different actions used in testing
   Action * actionA;
   Action * actionB;
   Phase * p1;
   Phase * p2;
   Phase * p3;
   Territory * t1;
   Unit * u1;
   
  public:
   /// \cond SETUPTEARDOWNACTIONTEST
   // initialization for the test action
   void setUp() {
      t1 = new LandTerritory(std::string("Spain"));
      p1 = new DefaultPhase(std::string("phase one"));
      p2 = new DefaultPhase(std::string("phase two"));
      p3 = new DefaultPhase(std::string("phase three"));
      u1 = new BuilderUnit(t1);
      //u2 = new BuilderUnit(t1);
      //delete actionA;
      //delete actionB;
      actionA = new BuildTraditionalArmyAction(p1, u1);
      actionB = new BuildTraditionalArmyAction(p2, u1);
   }

   // frees memory for the actions
   void tearDown() {
      delete actionA;
      delete actionB;
      delete p1;
      delete p2;
      delete p3;
      delete t1;
   }
   /// \endcond
   
   /// \test ensure that the action names are correctly reported
   void actionname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(actionA->name() == "BuildTraditionalArmy");
      CPPUNIT_ASSERT(actionB->name() == "BuildTraditionalArmy");
   }
   
   /// \test ensure that the action phases are correct
   void actionphase_should_be_as_constructed()  {
      CPPUNIT_ASSERT(actionA->applicable(p1) == true);
      CPPUNIT_ASSERT(actionB->applicable(p1) == false);
      CPPUNIT_ASSERT(actionB->applicable(p2) == true);
   }

   /// \test that doaction() adds units as appropriate
   void action_doaction_should_properly_add_units_to_territory()  {
      Territory::unitContainer myc;
      Territory::unitContainer::iterator myit;
      int numberOfUnits;      

      myc = t1->units(new FilterByAllUnitTypes(new TraditionalArmy(t1)));
      myit = myc.find("TraditionalArmy");
      CPPUNIT_ASSERT(myit == myc.end());

      actionA->doaction(1,t1);
      myc = t1->units(new FilterByAllUnitTypes(new TraditionalArmy(t1)));
      myit = myc.find("TraditionalArmy");
      CPPUNIT_ASSERT(myit != myc.end());
      numberOfUnits = myit->second->numUnits();
      CPPUNIT_ASSERT(numberOfUnits == 1);
    
      actionA->doaction(1,t1);
      myc = t1->units(new FilterByAllUnitTypes(new TraditionalArmy(t1)));
      myit = myc.find("TraditionalArmy");
      numberOfUnits = myit->second->numUnits();
      CPPUNIT_ASSERT(numberOfUnits == 2);
   }
};

/// \cond TestBuildTraditionalArmyActionREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestBuildTraditionalArmyAction);
/// \endcond
