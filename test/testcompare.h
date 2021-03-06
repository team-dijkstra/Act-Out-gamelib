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
 * \file testcompare.cc
 * Contains tests for name based comparison operators.
 */
#ifndef TEST_COMPARE_H
#define TEST_COMPARE_H

#include <map>
#include <functional>
#include <string>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "compare.h"
#include "functional.h"

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
   CPPUNIT_TEST(comparison_operators_work_with_stl_functional);
   CPPUNIT_TEST(comparison_operators_work_with_stl_containers);
   CPPUNIT_TEST(comparison_wrapper_is_convertible_from_wrapped_type);
   CPPUNIT_TEST_SUITE_END_ABSTRACT();
  protected:
   typedef T Nameable;
   typedef Compare<Nameable, std::string, &Nameable::name> cmp_t;
   virtual Nameable * createObject(const char * name) =0;
   
  public:

   /// \test ensure that Compare byname comparisons work for empty name 
   ///   strings.
   void empty_name_comparisons_yeild_equality_only() {
      
      CPPUNIT_ASSERT(cmp_t(*empty1) == cmp_t(*empty2));
      CPPUNIT_ASSERT(! (cmp_t(*empty1) < cmp_t(*empty2)));
      CPPUNIT_ASSERT(cmp_t(*empty1) <= cmp_t(*empty2));
      CPPUNIT_ASSERT(! (cmp_t(*empty1) > cmp_t(*empty2)));
      CPPUNIT_ASSERT(cmp_t(*empty1) >= cmp_t(*empty2));
   }

   /// \test ensure that Compare byname comparisons are valid for 
   ///   reflexive self comparisons.
   void self_comparison_yeilds_equality_only() {

      CPPUNIT_ASSERT(cmp_t(*obj1) == cmp_t(*obj1));
      CPPUNIT_ASSERT(! (cmp_t(*obj1) < cmp_t(*obj1)));
      CPPUNIT_ASSERT(cmp_t(*obj1) <= cmp_t(*obj1));
      CPPUNIT_ASSERT(! (cmp_t(*obj1) > cmp_t(*obj1)));
      CPPUNIT_ASSERT(cmp_t(*obj1) >= cmp_t(*obj1));
   }

   /// \test ensure that Compare byname comparisons are valid
   ///   for name strings that should be equal.
   void same_name_comparison_yeilds_equality_only() {

      CPPUNIT_ASSERT(cmp_t(*obj1) == cmp_t(*obj1a));
      CPPUNIT_ASSERT(! (cmp_t(*obj1) < cmp_t(*obj1a)));
      CPPUNIT_ASSERT(cmp_t(*obj1) <= cmp_t(*obj1a));
      CPPUNIT_ASSERT(! (cmp_t(*obj1) > cmp_t(*obj1a)));
      CPPUNIT_ASSERT(cmp_t(*obj1) >= cmp_t(*obj1a));
   }
   
   /// \test ensure that Compare byname comparisons are consistent for values
   ///   where one should be less than the other.
   void lessthan_operator_preserves_name_ordering() {
      
      if (obj1->name() < obj2->name()) {
         CPPUNIT_ASSERT(cmp_t(*obj1) < cmp_t(*obj2));
         CPPUNIT_ASSERT(cmp_t(*obj1) <= cmp_t(*obj2));
      } else if (obj2->name() < obj1->name()) {
         CPPUNIT_ASSERT(cmp_t(*obj2) < cmp_t(*obj1));
         CPPUNIT_ASSERT(cmp_t(*obj2) <= cmp_t(*obj1));
      }

      CPPUNIT_ASSERT(cmp_t(*obj1) <= cmp_t(*obj1a));
      CPPUNIT_ASSERT(cmp_t(*obj1a) <= cmp_t(*obj1));
   }
  
   /// \test ensure that Compare byname comparisons are consistent for values
   ///   where one should be greater than the other.
   void greaterthan_operator_preserves_name_ordering() {
      
      if (obj1->name() > obj2->name()) {
         CPPUNIT_ASSERT(cmp_t(*obj1) > cmp_t(*obj2));
         CPPUNIT_ASSERT(cmp_t(*obj1) >= cmp_t(*obj2));
      } else if (obj2->name() > obj1->name()) {
         CPPUNIT_ASSERT(cmp_t(*obj2) > cmp_t(*obj1));
         CPPUNIT_ASSERT(cmp_t(*obj2) >= cmp_t(*obj1));
      }
      
      CPPUNIT_ASSERT(cmp_t(*obj1) >= cmp_t(*obj1a));
      CPPUNIT_ASSERT(cmp_t(*obj1a) >= cmp_t(*obj1));
   }

   /// \test ensure that operators cooperate with the stl functional
   ///   comparators.
   void comparison_operators_work_with_stl_functional() {
      using function::binary::map;
      using util::dereference;

      map<std::less<cmp_t>, 
         dereference<Nameable>, 
         dereference<Nameable> > less;
      map<std::greater<cmp_t>,
         dereference<Nameable>,
         dereference<Nameable> > greater;
      map<std::less_equal<cmp_t>, 
         dereference<Nameable>, 
         dereference<Nameable> > less_eq;
      map<std::equal_to<cmp_t>, 
         dereference<Nameable>, 
         dereference<Nameable> > equal;
      map<std::greater_equal<cmp_t>, 
         dereference<Nameable>, 
         dereference<Nameable> > greater_eq;
      
      CPPUNIT_ASSERT(less(obj2, obj1));
      CPPUNIT_ASSERT(!less(obj1, obj2));
      CPPUNIT_ASSERT(!less(obj1, obj1a));
      CPPUNIT_ASSERT(greater(obj1, obj2));
      CPPUNIT_ASSERT(!greater(obj2, obj1));
      CPPUNIT_ASSERT(!greater(obj1, obj1a));
      CPPUNIT_ASSERT(less_eq(obj2, obj1));
      CPPUNIT_ASSERT(less_eq(obj1, obj1a));
      CPPUNIT_ASSERT(!less_eq(obj1, obj2));
      CPPUNIT_ASSERT(greater_eq(obj1, obj2));
      CPPUNIT_ASSERT(greater_eq(obj1, obj1a));
      CPPUNIT_ASSERT(!greater_eq(obj2, obj1));
      CPPUNIT_ASSERT(equal(obj1, obj1a));
      CPPUNIT_ASSERT(!equal(obj1, obj2));
      CPPUNIT_ASSERT(!equal(obj2, obj1));
   }

   /// \test ensure that the operators work with stl containers.
   void comparison_operators_work_with_stl_containers() {
      typedef std::map<Nameable*, int, std::greater<cmp_t> > map_t;

      map_t mymap;
      mymap.insert(std::make_pair(obj2, 2));
      mymap.insert(std::make_pair(obj1, 1));
      mymap.insert(std::make_pair(empty1, 3));
      
      typename map_t::iterator it2 = mymap.begin();
      typename map_t::iterator it1 = it2;
      ++it2;
      while (it2 != mymap.end()) {
         CPPUNIT_ASSERT(cmp_t((it1++)->first) > cmp_t((it2++)->first));
      }
   }

   /// \test ensure that it is possible to automatically wrap value 
   ///   and pointer types.
   void comparison_wrapper_is_convertible_from_wrapped_type() {
      cmp_t c1(obj1);
      cmp_t c2(*obj1);
      // note: the real test is that the object constructions above compile.
      // the following is almost a dummy test.
      CPPUNIT_ASSERT(c1 == c2);
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

#endif /* TEST_COMPARE_H */
