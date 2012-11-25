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
   CPPUNIT_TEST(empty_name_comparisons_yeild_equality_only);
   CPPUNIT_TEST(self_comparison_yeilds_equality_only);
   CPPUNIT_TEST(same_name_comparison_yeilds_equality_only);
   CPPUNIT_TEST(lessthan_operator_preserves_name_ordering);
   CPPUNIT_TEST(greaterthan_operator_preserves_name_ordering);
   //CPPUNIT_TEST(inequality_operator_preserves_strict_ordering);
   CPPUNIT_TEST_SUITE_END();
  protected:
   typedef T Nameable;
   virtual Nameable * createObject(const char * name) =0;
   
  public:

   void empty_name_comparisons_yeild_equality_only() {
      using namespace compare::byname;
      
      CPPUNIT_ASSERT(*empty1 == *empty2);
      CPPUNIT_ASSERT(! (*empty1 < *empty2));
      CPPUNIT_ASSERT(*empty1 <= *empty2);
      CPPUNIT_ASSERT(! (*empty1 > *empty2));
      CPPUNIT_ASSERT(*empty1 >= *empty2);
   }

   void self_comparison_yeilds_equality_only() {
      using namespace compare::byname;

      CPPUNIT_ASSERT(*obj1 == *obj1);
      CPPUNIT_ASSERT(! (*obj1 < *obj1));
      CPPUNIT_ASSERT(*obj1 <= *obj1);
      CPPUNIT_ASSERT(! (*obj1 > *obj1));
      CPPUNIT_ASSERT(*obj1 >= *obj1);
   }

   void same_name_comparison_yeilds_equality_only() {
      using namespace compare::byname;

      CPPUNIT_ASSERT(*obj1 == *obj1a);
      CPPUNIT_ASSERT(! (*obj1 < *obj1a));
      CPPUNIT_ASSERT(*obj1 <= *obj1a);
      CPPUNIT_ASSERT(! (*obj1 > *obj1a));
      CPPUNIT_ASSERT(*obj1 >= *obj1a);
   }
   
   void lessthan_operator_preserves_name_ordering() {
      using namespace compare::byname;
   
      if (obj1->name() < obj2->name()) {
         CPPUNIT_ASSERT(*obj1 < *obj2);
         CPPUNIT_ASSERT(*obj1 <= *obj2);
      } else if (obj2->name() < obj1->name()) {
         CPPUNIT_ASSERT(*obj2 < *obj1);
         CPPUNIT_ASSERT(*obj2 <= *obj1);
      } else {
         CPPUNIT_ASSERT(*obj1 <= *obj2);
         CPPUNIT_ASSERT(*obj2 <= *obj1);
      }
   }
   
   void greaterthan_operator_preserves_name_ordering() {
      using namespace compare::byname;
   
      if (obj1->name() > obj2->name()) {
         CPPUNIT_ASSERT(*obj1 > *obj2);
         CPPUNIT_ASSERT(*obj1 >= *obj2);
      } else if (obj2->name() > obj1->name()) {
         CPPUNIT_ASSERT(*obj2 > *obj1);
         CPPUNIT_ASSERT(*obj2 >= *obj1);
      } else {
         CPPUNIT_ASSERT(*obj1 >= *obj2);
         CPPUNIT_ASSERT(*obj2 >= *obj1);
      }
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

