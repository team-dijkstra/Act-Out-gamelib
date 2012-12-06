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
/** \file testmoveaction.cc
 * Contains tests for the MoveAction class
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "testaction.h"
#include "moveaction.h"
#include "defaultphase.h"
#include "landterritory.h"
#include "filterbyallunittypes.h"
#include "traditionalarmy.h"
#include "defaultplayer.h"
#include "filterbyunittype.h"
#include "config.h"

/// Class containing the test cases for MoveAction. The MoveAction
/// is exercised through its interface Action.
class TestMoveAction : public TestAction<MoveAction> {
   CPPUNIT_TEST_SUB_SUITE(TestMoveAction, TestAction<MoveAction>);
   CPPUNIT_TEST(action_should_be_applicable_only_for_redeploy_phase);
   CPPUNIT_TEST(action_doaction_should_properly_move);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different actions used in testing
   Action * actionA;
   Phase * p1, * p2, * p3;
   Player * o1, * o2;
   Territory * t1, * t2, * t3;

  protected:
   typedef MoveAction ActionType;

   Action * createAction(Unit * parent) {
      return new MoveAction(parent);
   }

   Unit * createUnit(Territory * location, int nunits = 1) {
      return new TraditionalArmy(location, nunits);
   }
   
  public:
   /// \cond SETUPTEARDOWNACTIONTEST
   // initialization for the test action
   void setUp() {
      TestAction<ActionType>::setUp();

      o1 = createPlayer("Player 1");
      o2 = createPlayer("Player 2");
      t1 = createTerritory("Spain", o1);
      t2 = createTerritory("Portugal", o2);
      t3 = createTerritory("France", o1);
      p1 = createPhase(phase::MARSHAL);
      p2 = createPhase(phase::ATTACK);
      p3 = createPhase(phase::REDEPLOY);
   }

   // frees memory for the actions
   void tearDown() {
      TestAction<ActionType>::tearDown();

      delete actionA;
      delete p1;
      delete p2;
      delete p3;
      delete t1;
      delete t2;
      delete t3;
      delete o1;
      delete o2;
   }
   /// \endcond
   
   /// \test ensure that the action phases are correct
   void action_should_be_applicable_only_for_redeploy_phase()  {
      Unit * u1 = createUnit(t1);
      actionA = createAction(u1);

      CPPUNIT_ASSERT(! actionA->applicable(p1));
      CPPUNIT_ASSERT(! actionA->applicable(p2));
      CPPUNIT_ASSERT(actionA->applicable(p3));

      delete u1;
   }

   /// \test that doaction() adds units as appropriate
   void action_doaction_should_properly_move()  {
      //added units to territory unitContainers

      Unit * u1 = createUnit(t1, 4);
      Unit * u2 = createUnit(t2);
      Unit * u3 = createUnit(t3);
      actionA = createAction(u1);
      
      t1->addUnit(u1);
      t2->addUnit(u2);
      t3->addUnit(u3);

      //check the owner of each unit->whereAt()
      CPPUNIT_ASSERT(u1->whereAt()->owner() == o1); 
      CPPUNIT_ASSERT(u2->whereAt()->owner() == o2);

      //check the owner of each territory
      CPPUNIT_ASSERT(t1->owner() == o1);
      CPPUNIT_ASSERT(t2->owner() == o2);
      CPPUNIT_ASSERT(t3->owner() == o1);
      
      //sending 100 guys from t1 to t2 which should fail because o1 does not own
      //t2.
      actionA->doaction(100, t2);

      //check the owner of each unit->whereAt() again
      CPPUNIT_ASSERT(u1->whereAt()->owner() == o1);
      CPPUNIT_ASSERT(u2->whereAt()->owner() == o2);

      //check the owner of territory 2 which should be the same
      CPPUNIT_ASSERT(t2->owner() == o2);

      //check the number of guys in each unit after the first 'move'
      CPPUNIT_ASSERT(u1->numUnits() == 4);
      CPPUNIT_ASSERT(u2->numUnits() == 1);
      CPPUNIT_ASSERT(u3->numUnits() == 1);

      actionA->setState();
      //send 1 guy from u1 to t3 which should work because o2 (the owner
      //of t3) has no defending units, but only with 4 guys
      actionA->doaction(1, t3);

      //check the number of guys in each unit after the second move
      //this is correct because u1 did not have 100 guys in the unit, but 4
      CPPUNIT_ASSERT(u1->numUnits() == 3);
      CPPUNIT_ASSERT(u2->numUnits() == 1);
      CPPUNIT_ASSERT(u3->numUnits() == 2);  
   }
};

/// \cond TestMoveActionREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestMoveAction);
/// \endcond
