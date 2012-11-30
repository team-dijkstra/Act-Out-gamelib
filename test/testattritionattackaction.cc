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
#include "attritionattackaction.h"
#include "defaultphase.h"
#include "landterritory.h"
#include "filterbyallunittypes.h"
#include "traditionalarmy.h"
#include "defaultplayer.h"

/// Class containing the test cases for AttritionAttackAction. The AttritionAttackAction
/// is exercised through its interface Action.
class TestAttritionAttackAction : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestAttritionAttackAction);
   CPPUNIT_TEST(actionname_should_be_as_constructed);
   CPPUNIT_TEST(actionphase_should_be_applicable_if_attack);
   CPPUNIT_TEST(action_unit_should_return_parent);
   CPPUNIT_TEST(action_source_should_return_parent_location);
   CPPUNIT_TEST(action_doaction_should_properly_attrition_attack);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different actions used in testing
   Action * actionA;
   Action * actionB;
   Phase * p1;
   Phase * p2;
   Player * o1, * o2;
   Territory * t1, * t2;
   Unit * u1, * u2;
   
  public:
   /// \cond SETUPTEARDOWNACTIONTEST
   // initialization for the test action
   void setUp() {
      o1 = new DefaultPlayer(std::string("Player 1"));
      o2 = new DefaultPlayer(std::string("Player 2"));
      t1 = new LandTerritory(std::string("Spain"), o1);
      t2 = new LandTerritory(std::string("Portugal"), o2); 
      p1 = new DefaultPhase(std::string("Attack"));
      p2 = new DefaultPhase(std::string("Marshall"));
      u1 = new TraditionalArmy(t1, 4);
      u2 = new TraditionalArmy(t2);
      actionA = new AttritionAttackAction(u1);
      actionB = new AttritionAttackAction(u2);
   }

   // frees memory for the actions
   void tearDown() {
      delete actionA;
      delete actionB;
      delete p1;
      delete p2;
      delete t1;
      delete t2;
      delete o1;
      delete o2;
   }
   /// \endcond
   
   /// \test ensure that the action names are correctly reported
   void actionname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(actionA->name() == "AttritionAttack");
      CPPUNIT_ASSERT(actionB->name() == "AttritionAttack");
      delete u1;
      delete u2;
   }
   
   /// \test ensure that only correct Phase objects return true
   void actionphase_should_be_applicable_if_attack()  {
      CPPUNIT_ASSERT(actionA->applicable(p1) == true);
      CPPUNIT_ASSERT(actionB->applicable(p2) == false);
      CPPUNIT_ASSERT(actionB->applicable(p1) == true);
      delete u1;
      delete u2;
   }

   /// \test ensure that unit is correctly reported
   void action_unit_should_return_parent()  {
      CPPUNIT_ASSERT(actionA->unit() == u1);
      CPPUNIT_ASSERT(actionB->unit() == u2);
      delete u1;
      delete u2;
   }

   /// \test ensure that source is correctly reported
   void action_source_should_return_parent_location()  {
      CPPUNIT_ASSERT(actionA->source() == t1);
      CPPUNIT_ASSERT(actionB->source() == t2);
      delete u1;
      delete u2;
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

   
   

};
/// \cond TestAttritionAttackActionREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestAttritionAttackAction);
/// \endcond
