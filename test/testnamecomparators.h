
/**
 * \file testnamecomparators.cc
 * Contains tests for name based comparison operators.
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "namecomparators.h"
#include "territory.h"

/**
 * Name based comparison operators test suite.
 * \tparam T the type of the objects to compare.
 */
template<typename T>
class TestNameComparators : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestNameComparators);
   CPPUNIT_TEST(comparisons_work_for_empty_strings);
   CPPUNIT_TEST_SUITE_END();
  protected:
   typedef T Nameable;
   virtual Nameable * createObject(const char * name) =0;
   
  public:

   void comparisons_work_for_empty_strings() {
      using namespace compare::byname;
      
      CPPUNIT_ASSERT(*empty1 == *empty2);
      CPPUNIT_ASSERT(! (*empty1 < *empty2));
      CPPUNIT_ASSERT(*empty1 <= *empty2);
      CPPUNIT_ASSERT(! (*empty1 > *empty2));
      CPPUNIT_ASSERT(*empty1 >= *empty2);
   }

   // let doxygen skip uninteresting methods.
   /// \cond
   void setUp() {
      obj1 = createObject("freddy");
      obj2 = createObject("eddie");
      obj1a = createObject("freddy");
      empty1 = createObject("");
      empty2 = createObject("");
   }

   void tearDown() {
      delete obj1;
      delete obj2;
      delete obj1a;
      delete empty1;
      delete empty2;
   }
   /// \endcond

  private:
   Nameable * obj1;
   Nameable * obj2;
   Nameable * obj1a;
   Nameable * empty1;
   Nameable * empty2;
};

