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

#include "testaction.h"
#include "buildtraditionalarmyaction.h"
#include "defaultphase.h"
#include "landterritory.h"
#include "filterbyallunittypes.h"
#include "traditionalarmy.h"
#include "builderunit.h"
#include "attritionattackaction.h"
#include "defaultplayer.h"
#include "config.h"

/// Class containing the test cases for BuildTraditionalArmyAction. The BuildTraditionalArmyAction
/// is exercised through its interface Action.
class TestBuildTraditionalArmyAction : public TestAction<BuildTraditionalArmyAction> {
   CPPUNIT_TEST_SUB_SUITE(TestBuildTraditionalArmyAction, TestAction<BuildTraditionalArmyAction>);
   CPPUNIT_TEST(action_should_be_applicable_only_for_marshal_phase);
   CPPUNIT_TEST(action_doaction_should_properly_add_units_to_territory);
   CPPUNIT_TEST_SUITE_END();
  
  private:
   // different actions used in testing
   Phase * p1;
   Phase * p2;
   Phase * p3;
   Player * o1;
   Territory * t1;
   Unit * u1;
   Action * actionA;
 
  protected:
   typedef BuildTraditionalArmyAction ActionType;

   Action * createAction(Unit * parent) {
      return new BuildTraditionalArmyAction(parent);
   }

   Unit * createUnit(Territory * location, int nunits = 1) {
      return new BuilderUnit(location, nunits);
   }

  public:
   
   /// \test ensure that the action phases are correct
   void action_should_be_applicable_only_for_marshal_phase()  {
      CPPUNIT_ASSERT(actionA->applicable(p1));
      CPPUNIT_ASSERT(! actionA->applicable(p2));
      CPPUNIT_ASSERT(! actionA->applicable(p3));
   }

   /// \test that doaction() adds units as appropriate
   void action_doaction_should_properly_add_units_to_territory()  {
      Territory::unitContainer myc;
      Territory::unitContainer::iterator myit;
      int numberOfUnits;      
      FilterByAllUnitTypes fat;

      myc = t1->units( &fat);
      myit = myc.find("TraditionalArmy");
      
      CPPUNIT_ASSERT(myit == myc.end());

      actionA->doaction(1,t1);
      myc = t1->units( &fat);
      myit = myc.find("TraditionalArmy");
      
      CPPUNIT_ASSERT(myit != myc.end());
      numberOfUnits = myit->second->numUnits();
      CPPUNIT_ASSERT(numberOfUnits == 1);
   
      actionA->setState();
      actionA->doaction(1,t1);
      myc = t1->units( &fat);
      myit = myc.find("TraditionalArmy");
      numberOfUnits = myit->second->numUnits();
      
      CPPUNIT_ASSERT(numberOfUnits == 2);
   }

   /// \cond SETUPTEARDOWNACTIONTEST
   // initialization for the test action
   void setUp() {
      TestAction<ActionType>::setUp();

      o1 = createPlayer("Player 1");
      t1 = createTerritory("Spain", o1);
      p1 = createPhase(phase::MARSHAL);
      p2 = createPhase(phase::ATTACK);
      p3 = createPhase(phase::REDEPLOY);

      u1 = createUnit(t1, 4);
      actionA = createAction(u1);
   }

   // frees memory for the actions
   void tearDown() {
      TestAction<ActionType>::tearDown();
      
      delete o1;
      delete u1;
      delete actionA;
      delete p1;
      delete p2;
      delete p3;
      delete t1;
   }
   /// \endcond

};

/// \cond TestBuildTraditionalArmyActionREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestBuildTraditionalArmyAction);
/// \endcond
