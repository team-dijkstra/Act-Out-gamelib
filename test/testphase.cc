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
 * cpsc 2720 - Project - Phase Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "concretephase.h"


/// Class containing the test cases for ConcretePhase. The ConcretePhase
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
   // initialization for the test phase
   void setUp() {
      delete phaseA;
      delete phaseB;
      phaseA = new ConcretePhase(std::string("Marshal Forces"));
      phaseB = new ConcretePhase(std::string("Attack"));
   }

   // frees memory for the phases
   void tearDown() {
      delete phaseA;
      delete phaseB;
   }

   /// \test ensure that the phase names are correctly reported
   void phasename_should_be_as_constructed()  {
      CPPUNIT_ASSERT(phaseA->name() == "Marshal Forces");
      CPPUNIT_ASSERT(phaseB->name() == "Attack");
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestPhase);

