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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "functional.h"

/**
 * Test cases for function composition utilities defined in functional.h
 */
class TestFunctional : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestFunctional);
   CPPUNIT_TEST(eq_should_discriminate_types);
   CPPUNIT_TEST(last_should_return_nil_for_empty_list);
   CPPUNIT_TEST(last_should_return_head_for_one_element_list);
   CPPUNIT_TEST(last_should_return_last_for_multi_element_list);
   CPPUNIT_TEST_SUITE_END();
  public:

   /// \test ensure that type::eq returns true for same types, and 
   ///  false for any other combination.
   void eq_should_discriminate_types() {
      bool result;

      result = type::eq<bool, bool>::value;
      CPPUNIT_ASSERT(result);

      result = type::eq<bool, char>::value;
      CPPUNIT_ASSERT(!result);
   }

   /// \test ensure that typelist::last works for empty lists.
   void last_should_return_nil_for_empty_list() {
      using namespace typelist;
      typedef nil list;
      const bool result = type::eq<nil, last<list>::type>::value;

      CPPUNIT_ASSERT(result);
   }

   /// \test ensure that typelist::last works for one element lists.
   void last_should_return_head_for_one_element_list() {
      using namespace typelist;
      typedef cons<int> mylist;
      const bool result = type::eq<mylist::head, last<mylist>::type>::value;

      CPPUNIT_ASSERT(result);
   }

   /// \test ensure that typelist::last works for non-trivial lists.
   void last_should_return_last_for_multi_element_list() {
      using namespace typelist;
      typedef cons<int, cons<bool, cons<char, cons<long> > > > mylist;
      const bool result = type::eq<long, last<mylist>::type>::value;

      CPPUNIT_ASSERT(result);
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFunctional);
