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
 * cpsc 2720 - Project - CompoundIteratorAdapter Test cases
 */

#include <vector>
#include <utility>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "compounditeratoradapter.h"

/// CompoundIteratorAdapter test suite.
class TestCompoundIteratorAdapter : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestCompoundIteratorAdapter);
   CPPUNIT_TEST(iterator_should_be_equal_to_self);
   CPPUNIT_TEST(iterators_to_same_element_should_be_equal);
   CPPUNIT_TEST(iterators_to_different_element_should_not_be_equal);
   CPPUNIT_TEST(iterator_dereference_should_yield_member_value);
   //CPPUNIT_TEST(preincrement_operator_should_advance_immediately);
   //CPPUNIT_TEST(postincrement_operator_should_advance_after);
   //CPPUNIT_TEST(predecrement_operator_should_regress_immediately);
   //CPPUNIT_TEST(postdecrement_operator_should_regress_after);
   CPPUNIT_TEST_SUITE_END();
  private:
   typedef int stype;
   typedef std::pair<stype, double> ctype;
   typedef std::vector<ctype> ctype_container;
   typedef ctype_container::iterator ctype_iterator;
   typedef CompoundIteratorAdapter<ctype_iterator, stype, &ctype::first> test_iterator;

   ctype_container tc;
  public:

   // let doxygen skip uninteresting methods
   /// \cond
   void setUp() {
      int j = 1;
      // make at least some adjacent pairs equal.
      for (int i = 0; i < 20; i += 1 + j) {
         j = -j;
         tc.push_back(std::make_pair(i, (double)i));
      }
   }

   void tearDown() {
      tc.clear();
   }
   /// \endcondThis file is part 

   /// \test ensure that a == a is true for the adapter.
   void iterator_should_be_equal_to_self() {
      ctype_iterator ci = tc.begin();
      test_iterator ti(ci);

      CPPUNIT_ASSERT(ti == ti);
   }

   /// \test ensure that different iterators pointing to the same element are equal.
   void iterators_to_same_element_should_be_equal() {
      ctype_iterator ci = tc.begin();
      test_iterator ti1(ci);
      test_iterator ti2(ci);

      CPPUNIT_ASSERT(ti1 == ti2);
   }

   /// \test ensure that iterators pointing to different elements are not equal.
   void iterators_to_different_element_should_not_be_equal() {
      ctype_iterator ci1 = tc.begin();
      ctype_iterator ciend = tc.end();
      ctype_iterator ci2 = ci1;
      ci2++;

      test_iterator ti1(ci1);
      test_iterator ti2(ci2);
      test_iterator tiend(ciend);

      while (ti2 != tiend) {
         CPPUNIT_ASSERT(ti1++ != ti2++);
      }
      
   }

   /// \test ensure that the pointer dereference operator works.
   ///       The value should be the same as the native iterator component value. 
   void iterator_dereference_should_yield_member_value() {
      ctype_iterator ci1 = tc.begin();
      ctype_iterator ci2 = ci1;
      ctype_iterator ciend = tc.end();
      
      test_iterator ti1(ci1);
      test_iterator tiend(ciend);

      while (ti1 != tiend) {
         stype si2 = ci2->first;
         //CPPUNIT_ASSERT(*ti1 == si2);
         ti1++;
         ci2++;
      }
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestCompoundIteratorAdapter);

