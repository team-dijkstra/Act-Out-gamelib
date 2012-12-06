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
   CPPUNIT_TEST(action_starts_in_ready_state);
   CPPUNIT_TEST(action_set_state_changes_state);
   CPPUNIT_TEST(action_set_state_returns_to_ready_with_no_args);
   CPPUNIT_TEST(doaction_changes_state_to_invalid_or_succeeded);
   CPPUNIT_TEST(action_status_reflects_state);
   CPPUNIT_TEST(action_status_includes_action_name);
   CPPUNIT_TEST_FAIL(action_description_has_name_unit_and_territory);
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
      CPPUNIT_ASSERT(actionA->unit() == u1);
   }

   /// \test ensure that source is correctly reported
   void action_source_should_return_parent_location()  {
      CPPUNIT_ASSERT(actionA->source() == t1);
   }

   /// \test ensure that the action starts in the correct state.
   void action_starts_in_ready_state() {
      CPPUNIT_ASSERT(actionA->state() == Action::State::READY);
   }

   /// \test ensure that the set state method changes state to the specified
   ///   state.
   void action_set_state_changes_state() {
      Action::State prev = actionA->state();
      actionA->setState(Action::State::SUCCEEDED);
      
      CPPUNIT_ASSERT(prev != actionA->state());
      CPPUNIT_ASSERT(actionA->state() == Action::State::SUCCEEDED);
   }

   /// \test ensure that the state is properly reset when setState called with 
   ///   no args.
   void action_set_state_returns_to_ready_with_no_args() {
      actionA->setState(Action::State::INVALID);
      
      CPPUNIT_ASSERT(actionA->state() == Action::State::INVALID);
      
      actionA->setState();

      CPPUNIT_ASSERT(actionA->state() == Action::State::READY);
   }

   /// \test ensure that the doaction transitions to a valid state.
   void doaction_changes_state_to_invalid_or_succeeded() {
      actionA->doaction(1, t1);
     
      bool status_is_SUCCEEDED_FAILED_or_INVALID =
         actionA->state() == Action::State::SUCCEEDED
         || actionA->state() == Action::State::FAILED
         || actionA->state() == Action::State::INVALID;
         
      CPPUNIT_ASSERT(status_is_SUCCEEDED_FAILED_or_INVALID);
   }

   /// \test ensure that the status messages reflect the reported state of 
   //    the system.
   void action_status_reflects_state() {
      
      /// \todo Brittle tests.
      actionA->setState(Action::State::READY);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find("ready"));
      
      actionA->setState(Action::State::PENDING);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find("pending"));
      
      actionA->setState(Action::State::SUCCEEDED);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find("success"));

      actionA->setState(Action::State::FAILED);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find("failed"));

      actionA->setState(Action::State::INVALID);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find("not valid"));
   }

   /// \test ensure that the name of the action is included in all status messages.
   void action_status_includes_action_name() {

      std::string myname = actionA->name();
            
      /// \todo Brittle tests.
      actionA->setState(Action::State::READY);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find(myname));
      
      actionA->setState(Action::State::PENDING);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find(myname));
      
      actionA->setState(Action::State::SUCCEEDED);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find(myname));

      actionA->setState(Action::State::FAILED);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find(myname));

      actionA->setState(Action::State::INVALID);
      CPPUNIT_ASSERT(std::string::npos != actionA->status().find(myname));

   }

   void action_description_has_name_unit_and_territory() {
      CPPUNIT_FAIL("not implemented");
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

