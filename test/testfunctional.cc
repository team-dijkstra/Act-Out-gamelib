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

#include <functional>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "functional.h"

/**
 * Test data for function composition test cases.
 */
struct twice {
   typedef int result_type;
   typedef int argument_type;
   result_type operator()(argument_type x) {
      return x + x;
   }
};

/**
 * Test cases for function composition utilities defined in functional.h
 */
class TestFunctional : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestFunctional);
   CPPUNIT_TEST(eq_should_discriminate_types);
   CPPUNIT_TEST(last_should_return_nil_for_empty_list);
   CPPUNIT_TEST(last_should_return_head_for_one_element_list);
   CPPUNIT_TEST(last_should_return_last_for_multi_element_list);
   CPPUNIT_TEST(unary_map_should_produce_equivalent_functor_for_single_element_list);
   CPPUNIT_TEST(unary_map_should_produce_composite_functor_for_multi_element_list);
   CPPUNIT_TEST(binary_map_should_produce_equivalent_functor_for_null_mapping);
   CPPUNIT_TEST(binary_map_should_do_parameter_mapping);
   CPPUNIT_TEST(dereference_should_convert_pointer_to_ref);
   CPPUNIT_TEST(binary_map_should_work_with_stl_binary_functions);
   CPPUNIT_TEST(util_first_should_retrieve_reference_to_pair_first);
   CPPUNIT_TEST(util_second_should_retrieve_reference_to_pair_second);
   CPPUNIT_TEST_SUITE_END();

  private:
   struct f_bin_null {
      typedef int result_type;
      typedef int first_argument_type;
      typedef int second_argument_type;
      result_type operator()(first_argument_type x, second_argument_type y) {
         return x + y;
      }
   };

   struct f1_null {
      typedef int result_type;
      typedef int argument_type;
      result_type operator()(argument_type x) {
         return x;
      }
   };

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

   /// \test ensure that function::unary::map works for the base case.
   void unary_map_should_produce_equivalent_functor_for_single_element_list() {
      using namespace typelist;

      typedef function::unary::map<cons<f1_null> > fc;
      
      for (int i = 0; i < 10; ++i) {
         CPPUNIT_ASSERT(f1_null()(i) == fc()(i));
      }
   }

   /// \test ensure that function::unary::map properly composes multi-element lists.
   void unary_map_should_produce_composite_functor_for_multi_element_list() {
      using namespace typelist;
      
      typedef function::unary::map<cons<twice, cons<twice> > > twice2;

      // due to a bug in gcc these have to be instantiated separately.
      // instantiating these inline generates an 'ambiguous base' error.
      twice f1;
      twice2 f2;

      for (int i = -2; i < 10; ++i) {
         CPPUNIT_ASSERT(f2(i) == f1(f1(i)));
      }
   }

   /// \test ensure that function::binary::map works for null parameter mapping.
   void binary_map_should_produce_equivalent_functor_for_null_mapping() {

      typedef function::binary::map<f_bin_null> fc;

      for (int i = -2; i < 10; ++i) {
         for (int j = -2; j < 10; ++j) {
            CPPUNIT_ASSERT(f_bin_null()(i, j) == fc()(i, j));
         }
      }
   }

   /// \test ensure that function::binary::map works for single parameter mapping.
   void binary_map_should_do_parameter_mapping() {
      using typelist::nil;

      typedef function::binary::map<f_bin_null, twice> fc1;
      typedef function::binary::map<f_bin_null, nil, twice> fc2;
      typedef function::binary::map<f_bin_null, twice, twice> fc12;

      for (int i = -2; i < 10; ++i) {
         for (int j = -2; j < 10; ++j) {
            CPPUNIT_ASSERT(f_bin_null()(twice()(i), j) == fc1()(i, j));
            CPPUNIT_ASSERT(f_bin_null()(i, twice()(j)) == fc2()(i, j));
            CPPUNIT_ASSERT(f_bin_null()(twice()(i), twice()(j)) == fc12()(i, j));
         }
      }
   }
   /// \test ensure that function::binary::map works with stl binary_function functors.
   void binary_map_should_work_with_stl_binary_functions() {
      
      typedef function::binary::map<std::less<int>, util::dereference<int>, util::dereference<int> > ptrless;

      int i = 0;
      int j = 1;

      CPPUNIT_ASSERT(ptrless()(&i, &j));
      CPPUNIT_ASSERT(!ptrless()(&j, &i));
   }

   /// \test ensure that util::dereference functor works as expected.
   void dereference_should_convert_pointer_to_ref() {
      
      for (int i = 0; i < 10; ++i) {
         // const correct
         CPPUNIT_ASSERT(i == util::dereference<const int>()(&i));
      }

      int j = 2;
      // supports modification.
      util::dereference<int>()(&j) = 4;
      CPPUNIT_ASSERT(4 == j);
   }

   /// \test ensure that util::first properly maps std::pair.first to a
   ///   reference type.
   void util_first_should_retrieve_reference_to_pair_first() {
      typedef std::pair<int, double> pair_t;
      typedef util::first<pair_t> first_t;

      pair_t p;
      p.first = 2;
      p.second = 3.14;

      CPPUNIT_ASSERT(first_t()(p) == p.first);

      // supports modification.
      first_t()(p) = 3;
      CPPUNIT_ASSERT(3 == p.first);
   }
   
   /// \test ensure that util::second properly maps std::pair.second to a
   ///   reference type.
   void util_second_should_retrieve_reference_to_pair_second() {
      typedef std::pair<int, double> pair_t;
      typedef util::second<pair_t> second_t;

      pair_t p;
      p.first = 2;
      p.second = 3.14;

      CPPUNIT_ASSERT(second_t()(p) == p.second);

      // supports modification.
      second_t()(p) = 3.219;
      CPPUNIT_ASSERT(3.219 == p.second);
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFunctional);
