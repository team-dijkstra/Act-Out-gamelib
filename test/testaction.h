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

/**
 * \file testaction.h
 *
 * Contains tests for Action implementations.
 */
#ifndef TEST_ACTION_H
#define TEST_ACTION_H

#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "defaultaction.h"
//#include "territory.h"
//#include "unit.h"

#include "landterritory.h"
#include "defaultphase.h"
#include "defaultplayer.h"

/**
 * Action implementations test suite.
 */
template<typename T>
class TestAction : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestAction);
   CPPUNIT_TEST(actionname_should_be_overridden);
   CPPUNIT_TEST(actionname_should_be_classname);
   CPPUNIT_TEST(action_unit_should_return_parent);
   CPPUNIT_TEST(action_source_should_return_parent_location);
   CPPUNIT_TEST_SUITE_END_ABSTRACT();
  private:

   typedef T ActionType;

   // different objects used in testing
   Action * actionA; 
   Territory * t1;
   Unit * u1;

  protected:
   
   virtual Action * createAction(Unit * parent) =0;
      
   virtual Unit * createUnit(Territory * location, int nunits = 1) =0;
   
   virtual Territory * createTerritory(std::string name, Player * owner = NULL) {
      return new LandTerritory(name, owner);
   }

   virtual Phase * createPhase(std::string name) {
      return new DefaultPhase(name);
   }

   virtual Player * createPlayer(std::string name) {
      return new DefaultPlayer(name);
   }

  public:

      /// \test ensure that the action names are correctly reported
   void actionname_should_be_overridden()  {
      CPPUNIT_ASSERT(actionA->name() != DefaultAction::NAME);
   }

   /// \test ensure that the action names are correctly reported
   void actionname_should_be_classname()  {
      CPPUNIT_ASSERT(actionA->name() == ActionType::NAME);
   }

   /// \test ensure that unit is correctly reported
   void action_unit_should_return_parent()  {
      /// \todo should this really compare pointer values?
      CPPUNIT_ASSERT(actionA->unit() == u1);
   }

   /// \test ensure that source is correctly reported
   void action_source_should_return_parent_location()  {
      /// \todo pointer value comparison?
      CPPUNIT_ASSERT(actionA->source() == t1);
   }

   /// \cond SETUPTEARDOWNACTIONTEST
   // initialization for the test action
   void setUp() {
      t1 = createTerritory("Spain");
      u1 = createUnit(t1);
      actionA = createAction(u1);
   }

   // frees memory for the actions
   void tearDown() {
      delete actionA;
      delete t1;
      delete u1;
   }
   /// \endcond
};

#endif /* TEST_ACTION_H */

