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
   CPPUNIT_TEST_SUITE_END();
  private:
   typedef int stype;
   typedef std::pair<stype, double> ctype;
   typedef std::vector<ctype> ctype_container;
   typedef ctype_container::iterator ctype_iterator;
   typedef CompoundIteratorAdapter<ctype_iterator, ctype> test_iterator;

   ctype_container tc;
  public:

   // let doxygen skip uninteresting methods
   /// \cond
   void setUp() {
      for (int i = 0; i < 20; i++) {
          tc.push_back(std::make_pair(i, (double)i));
      }
   }

   void tearDown() {
      tc.clear();
   }
   /// \endcond

   void iterator_should_be_equal_to_self() {
      ctype_iterator ci = tc.begin();
      test_iterator ti(ci);

      CPPUNIT_ASSERT(ti == ti);
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestCompoundIteratorAdapter);

