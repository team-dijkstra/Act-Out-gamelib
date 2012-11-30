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
/** \file testdefaultphase.cc
 * Contains tests for the DefaultPhase class
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "defaultphase.h"

using namespace game;

/// Class containing the test cases for DefaultPhase. The DefaultPhase
/// is exercised through its interface Phase.
class TestPhase : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestPhase);
   CPPUNIT_TEST(phasename_should_be_as_constructed);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different phases used in testing
   Phase * phaseA;
   Phase * phaseB;
   
  public:
   /// \cond SETUPTEARDOWNPHASETEST
   // initialization for the test phase
   void setUp() {
      delete phaseA;
      delete phaseB;
      phaseA = new DefaultPhase(std::string("Marshal Forces"));
      phaseB = new DefaultPhase(std::string("Attack"));
   }
   // frees memory for the phases
   void tearDown() {
      delete phaseA;
      delete phaseB;
   }
   /// \endcond
   
   /// \test ensure that the phase names are correctly reported
   void phasename_should_be_as_constructed()  {
      CPPUNIT_ASSERT(phaseA->name() == "Marshal Forces");
      CPPUNIT_ASSERT(phaseB->name() == "Attack");
   }

};
/// \cond TestPhaseREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestPhase);
/// \endcond
