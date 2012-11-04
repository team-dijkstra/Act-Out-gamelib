/*
 * cpsc 2720 - Project - Phase Test cases
 */

#ifndef __TESTBOARD_H
#define __TESTBOARD_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sstream>
#include "ConcretePhase.h"


/// Class containing the test cases for ConcretePhase. The ConcretePhase
/// is exercised through its interface Phase.
class TestPhase : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestPhase);
   CPPUNIT_TEST(testPhaseName);
//	CPPUNIT_TEST_EXCEPTION(testOpenTileThrowsException, OutsideTheBoardException);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   /// different boards used in testing
   Phase phaseA *, phaseB *;
   
  public:
   /// initialization for the test phase
   void setUp() {
      phaseA = new ConcretePhase("Marshal Forces");
      phaseB = new ConcretePhase("Attack");
   }

   /// frees memory for the boards
   void tearDown() {
      delete phaseA;
      delete phaseB;
   }

   /// test that the board dimensions are correctly reported
   void testPhaseName()  {
      CPPUNIT_ASSERT(phaseA->name() == "Marshal Forces");
      CPPUNIT_ASSERT(phaseB->name() == "Attack");
   }


};

#endif
