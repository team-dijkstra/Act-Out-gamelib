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
#include "moveaction.h"
#include "defaultphase.h"
#include "landterritory.h"
#include "filterbyallunittypes.h"
#include "traditionalarmy.h"
#include "defaultplayer.h"
#include "filterbyunittype.h"

/// Class containing the test cases for MoveAction. The MoveAction
/// is exercised through its interface Action.
class TestMoveAction : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestMoveAction);
   CPPUNIT_TEST(actionname_should_be_as_constructed);
   CPPUNIT_TEST(actionphase_should_be_applicable_if_marshall);
   CPPUNIT_TEST(action_doaction_should_properly_move);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different actions used in testing
   Action * actionA;
   Action * actionB;
   Phase * p1;
   Phase * p2;
   Player * o1, * o2;
   Territory * t1, * t2, * t3;
   Unit * u1, * u2, * u3;
   //Territory::unitContainer t3sUnits;
   //Territory::unitContainer::iterator it;
   
  public:
   /// \cond SETUPTEARDOWNACTIONTEST
   // initialization for the test action
   void setUp() {
      o1 = new DefaultPlayer(std::string("Player 1"));
      o2 = new DefaultPlayer(std::string("Player 2"));
      t1 = new LandTerritory(std::string("Spain"), o1);
      t2 = new LandTerritory(std::string("Portugal"), o2);
      t3 = new LandTerritory(std::string("France"), o1);
      p1 = new DefaultPhase(std::string("Attack"));
      p2 = new DefaultPhase(std::string("Marshall"));
      u1 = new TraditionalArmy(t1, 4);
      u2 = new TraditionalArmy(t2);
      u3 = new TraditionalArmy(t3);
      actionA = new MoveAction(p2, u1);
      actionB = new MoveAction(p2, u2);

      //t3sUnits = t3->units(new FilterByUnitType(u1));
      //it = t3sUnits.find("TraditionalArmy");
      //u3 = it->second;
   }

   // frees memory for the actions
   void tearDown() {
      delete actionA;
      delete actionB;
      delete p1;
      delete p2;
      delete t1;
      delete t2;
      delete u1;
      delete u2;
   }
   /// \endcond
   
   /// \test ensure that the action names are correctly reported
   void actionname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(actionA->name() == "Move");
      CPPUNIT_ASSERT(actionB->name() == "Move");
   }
   
   /// \test ensure that the action phases are correct
   void actionphase_should_be_applicable_if_marshall()  {
      CPPUNIT_ASSERT(actionA->applicable(p2) == true);
      CPPUNIT_ASSERT(actionB->applicable(p1) == false);
      CPPUNIT_ASSERT(actionB->applicable(p2) == true);
   }

   /// \test that doaction() adds units as appropriate
   void action_doaction_should_properly_move()  {
      //added units to territory unitContainers

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

CPPUNIT_TEST_SUITE_REGISTRATION(TestMoveAction);

