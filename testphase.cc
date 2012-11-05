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

