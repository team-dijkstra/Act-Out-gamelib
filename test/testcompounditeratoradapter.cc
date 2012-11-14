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
   CPPUNIT_TEST_SUITE_END();
  private:
   typedef std::vector<std::pair<int, double> > test_container;
   typedef test_container::iterator test_iterator;
   typedef typename std::iterator_traits<test_iterator>::value_type outer_value_type;
   typedef CompoundIteratorAdapter<
      test_iterator,
      typename outer_value_type::first_type //, 
      //&iterator_traits<test_iterator>::value_type::first
      > first_iterator;
   
   typedef CompoundIteratorAdapter<
      test_iterator, 
      typename outer_value_type::first_type //, 
      //&iterator_traits<test_iterator>::value_type::second
      > second_iterator;
   

   test_container tc;
   first_iterator * fi;
   first_iterator * fi_end;
   second_iterator * si;
   second_iterator * si_end;
  public:

   // let doxygen skip uninteresting methods
   /// \cond
   void setUp() {
      for (int i = 0; i < 20; i++) {
          tc.push_back(std::make_pair(i, (double)i));
      }
      //fi = new first_iterator(tc.begin(), &first_iterator::value_type);
   }

   void tearDown() {
      tc.clear();
      delete fi;
      delete fi_end;
      delete si;
      delete si_end;
   }
   /// \endcond


};

CPPUNIT_TEST_SUITE_REGISTRATION(TestCompoundIteratorAdapter);

