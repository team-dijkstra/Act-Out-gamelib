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
/** \file testattritionattackaction.cc
 * Contains tests for the AttritionAttackAction class
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "testaction.h"
#include "attritionattackaction.h"
#include "defaultphase.h"
#include "landterritory.h"
#include "filterbyallunittypes.h"
#include "traditionalarmy.h"
#include "defaultplayer.h"
#include "config.h"

/// Class containing the test cases for AttritionAttackAction. The AttritionAttackAction
/// is exercised through its interface Action.
class TestAttritionAttackAction : public TestAction<AttritionAttackAction> {
   CPPUNIT_TEST_SUB_SUITE(TestAttritionAttackAction, TestAction<AttritionAttackAction>);
   CPPUNIT_TEST(action_should_be_applicable_only_for_attack_phase);
   CPPUNIT_TEST(action_doaction_should_properly_attrition_attack);
   CPPUNIT_TEST_SUITE_END();
  
  private:
   // different actions used in testing
   Phase * p1;
   Phase * p2;
   Phase * p3;
   Player * o1, * o2;
   Territory * t1, * t2;
   Unit * u1, * u2;
   Action * actionA;

  protected:
   typedef AttritionAttackAction ActionType;

   Action * createAction(Unit * parent) {
      return new AttritionAttackAction(parent);
   }

   Unit * createUnit(Territory * location, int nunits = 1) {
      return new TraditionalArmy(location, nunits);
   }

  public:
  
   /// \test ensure that only correct Phase objects return true
   void action_should_be_applicable_only_for_attack_phase()  {
      CPPUNIT_ASSERT(! actionA->applicable(p1));
      CPPUNIT_ASSERT(actionA->applicable(p2));
      CPPUNIT_ASSERT(! actionA->applicable(p3));
   }

   /// \test that doaction() adds units as appropriate
   void action_doaction_should_properly_attrition_attack()  {
      //added units to territory unitContainers
      t1->addUnit(u1);
      t2->addUnit(u2);

      //check the owner of each unit->whereAt()
      CPPUNIT_ASSERT(u1->whereAt()->owner() == o1); 
      CPPUNIT_ASSERT(u2->whereAt()->owner() == o2);

      //send 1 guy from unit u1 to attack the unit of the same type on another territory
      actionA->doaction(1, t2);

      //check the owner of each unit->whereAt() again
      CPPUNIT_ASSERT(u1->whereAt()->owner() == o1);
      CPPUNIT_ASSERT(u2->whereAt()->owner() == o2);

      //check the number of guys in each unit after the first attack
      CPPUNIT_ASSERT(u1->numUnits() == 3);
      CPPUNIT_ASSERT(u2->numUnits() == 0);

      //send 100 guys from u1 to attack t2
      actionA->doaction(100, t2);

      //check the owner of each unit->whereAt() after the second attack
      CPPUNIT_ASSERT(u1->whereAt()->owner() == o1);
      CPPUNIT_ASSERT(u2->whereAt()->owner() == o1);

      //check the number of guys in each unit after the second attack
      //this is correct because u1 did not have 100 guys in the unit, but 3
      CPPUNIT_ASSERT(u1->numUnits() == 0);
      CPPUNIT_ASSERT(u2->numUnits() == 3);
   }

   /// \cond SETUPTEARDOWNACTIONTEST
   // initialization for the test action
   void setUp() {
      TestAction<ActionType>::setUp();

      o1 = createPlayer("Player 1");
      o2 = createPlayer("Player 2");
      t1 = createTerritory("Spain", o1);
      t2 = createTerritory("Portugal", o2); 
      p1 = createPhase(phase::MARSHAL);
      p2 = createPhase(phase::ATTACK);
      p3 = createPhase(phase::REDEPLOY);

      u1 = createUnit(t1, 4);
      u2 = createUnit(t2);
      actionA = createAction(u1);
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
   }
   /// \endcond
 

};
/// \cond TestAttritionAttackActionREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestAttritionAttackAction);
/// \endcond
