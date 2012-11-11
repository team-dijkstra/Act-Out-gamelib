/*
 * cpsc 2720 - Project - Action Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "buildtraditionalarmyaction.h"
#include "concretephase.h"


/// Class containing the test cases for BuildTraditionalArmyAction. The BuildTraditionalArmyAction
/// is exercised through its interface Action.
class TestAction : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestAction);
   CPPUNIT_TEST(actionname_should_be_as_constructed);
   CPPUNIT_TEST(actionphase_should_be_as_constructed);
   CPPUNIT_TEST_SUITE_END();
   
  private:
   // different actions used in testing
   Action * actionA;
   Action * actionB;
   Phase * p1;
   Phase * p2;
   
  public:
   // initialization for the test action
   void setUp() {
      p1 = new ConcretePhase(std::string("phase one"));
      p2 = new ConcretePhase(std::string("phase two"));
      delete actionA;
      delete actionB;
      actionA = new BuildTraditionalArmyAction(p1);
      actionB = new BuildTraditionalArmyAction(p2);
   }

   // frees memory for the actions
   void tearDown() {
      delete actionA;
      delete actionB;
      delete p1;
      delete p2;
   }

   /// \test ensure that the action names are correctly reported
   void actionname_should_be_as_constructed()  {
      CPPUNIT_ASSERT(actionA->name() == "BuildTraditionalArmy");
      CPPUNIT_ASSERT(actionB->name() == "BuildTraditionalArmy");
   }
   
   /// \test ensure that the action phases are correct
   void actionphase_should_be_as_constructed()  {
      CPPUNIT_ASSERT(actionA->applicable(p1) == true);
      CPPUNIT_ASSERT(actionB->applicable(p2) == true);
   }

   
   

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestAction);

