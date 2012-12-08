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
 * \file functional.h
 * 
 * contains various template metafunctions that facilitate type and function
 * composition.
 *
 * \author Matt Voroney
 */

#ifndef TEMPLATE_FUNCTIONAL_H
#define TEMPLATE_FUNCTIONAL_H

/* forward declarations */
/*===========================================================================*/

/**
 * \namespace util
 *
 * The util namespace contains convenient utility templates that don't clearly
 * belong anywhere else.
 */
namespace util {
   
   /**
    * Dereferences a pointer to T, so that the value of T can be used and
    * modified. This operation also optionally converts from a source type
    * to a destination type. By default source and desination types are the
    * same.
    *
    * \tparam T The source type to map pointers to references. So if T=int,
    *  the defined mapping will be from int* to int&
    * \tparam U The destination type. defaults to T.
    */
   template<typename T, typename U = T> 
   struct dereference;

   /**
    * A binary functor that takes a comparator (or a functor that returns 
    * convertable to bool), and deletes the second object if T::operator(x, y) 
    * returns true. This is useful for applying some stl algorithms such as
    * std::unique to stl containers of pointer types, which would otherwise
    * result in memory leaks.
    *
    * \tparam T A binary functor that returns convertible to bool. This functor
    *   is expected to conform to the stl conventions and must supply typedefs
    *   for \c first_argument_type, \c second_argument_type, and \c result_type.
    *   \c first_argument_type and \c second_argument_type will be mapped to 
    *   pointer types since this functor does not make any sense otherwise.
    */
   template<typename T>
   struct delete_if;

   /**
    * A unary functor that calls the supplied pointer to member function on
    * the passed object.
    *
    * \deprecated This functor is a near duplicate of std::const_mem_fun_t, 
    *   and more general facilities are possible. 
    *
    * \tparam T The type of the object supplying the member function.
    * \tparam AttrT The return type of the pointer to member function.
    * \tparam Tattr The pointer to member function to invoke on passed 
    *   instances of T.
    */
   template<typename T, typename AttrT, AttrT (T::*Tattr)() const>
   struct member;
}

/**
 * \namespace type
 *
 * This namespace contains various type mapping and deduction templates that
 * can be used for type and functional composition. Useful for template 
 * metaprogramming.
 */
namespace type {
   /// used to indicate that a type is true. useful for type deductions.
   struct true_tag;
   /// used to indicate that a type is "false". useful for type deductions. 
   struct false_tag;

   /**
    * Checks whether T and U are the same type. Implementations will define
    * a \c value member constant that will be \c true if T and U were the same
    * type, or \c false if T and U were different types. 
    *
    * \tparam T The type to compare with U.
    * \tparam U The type to compare with T.
    */
   template<typename T, typename U> 
   struct eq;

   /**
    * \namespace type::qualifier
    *
    * This namespace contains various type qualifier manipulation metafunctions.
    * These metafunctions allow you to operate on the constness, volatility, 
    * pointerness or (lvalue) refness of types.
    */
   namespace qualifier {

      /**
       * Strip the qualifiers of U from T.
       * 
       * \tparam T The type to strip qualifiers from.
       * \tparam U A type specifiying the qualifiers to strip. Defaults to T. 
       */
      template<typename T, typename U = T>
      struct strip;

      /**
       * Copy the qualifiers of T onto U that are present in V.
       * 
       * \tparam T The type whose qualifiers will be copied.
       * \tparam U The type to copy the qualifiers of T to.
       * \tparam V A type specifying the qualifiers to copy. Defaults to T.
       */
      template<typename T, typename U, typename V = T>
      struct copy;
   }
}

/**
 * \namespace typelist
 *
 * This namespace contains various metafunctions for manipulating simple
 * typelists. The manipulations will work on simple cons lists.
 */
namespace typelist {
   /// sentinel node.
   struct nil;
   
   /**
    * Construct a list. Prepends H onto T
    *
    * \tparam H The new head of the list.
    * \tparam T The list to attach the head to. Will become the tail of 
    *   the new list. Defaults to \c nil
    * 
    * \see nil Used as the list terminal
    */
   template<typename H, typename T = nil>
   struct cons;

   /**
    * Retrieves the last element of the list, immediately preceeding the
    * terminal node. This will simply be the head if the supplied tail was
    * typelist::nil.
    *
    * \tparam head The head of the list to retrieve the last of.
    * \tparam tail The tail of the list to retrieve the last of. Defaults to
    *   typelist::nil.
    *
    * \see last Top level driver.
    */
   template<typename head, typename tail = nil>
   struct last2;

   /**
    * Retrieves the last element of the list, immediately preceeding the
    * terminal node, or nil if the supplied list was empty. This is a 
    * convenience top level runner.
    *
    * \tparam list The list to retrieve the last element from. defaults to nil.
    *
    * \see last2 The internal implementation class.
    */
   template<typename list = nil>
   struct last;
}

/**
 * \namespace function
 *
 * This namespace contains various metafunctions for function composition.
 */
namespace function {
   struct binary_tag;
   struct unary_tag;

   /**
    * \namespace function::binary
    *
    * This namespace contains metafunctions for composing and manipulating
    * binary functors.
    */
   namespace binary {
      using typelist::nil;

      /**
       * This metafunction composes a binary functor from the supplied base
       * binary functor F1, and adds parameter mappings defined by typelists 
       * of unary functions, F2 and F3 to the input parameters of F1. All
       * manipulated functors are expected to conform to the stl conventions.
       *
       * \tparam F1 The base binary function to compose. Must supply typedefs
       *    for \c first_argument_type, \c second_argument_type, and 
       *    \c result_type.
       * \tparam F2 A typelist of unary functors defining a transformation 
       *    sequence from F2::argument_type to F1::first_argument_type. 
       *    Defaults to typelist::nil. Must supply typedefs for 
       *    \c argument_type, and \c result_type.
       * \tparam F3 A typelist of unary functors defining a transformation
       *    sequence from F3::argument_type to F1::second_argument_type.
       *    Defaults to typelist::nil. Must supply typedefs for 
       *    \c argument_type, and \c result_type.
       *
       * \see typelist
       */
      template<typename F1, typename F2 = nil, typename F3 = nil>
      struct map;
   }

   /**
    * \namespace function::unary
    *
    * This namespace contains metafunctions for composing and manipulating
    * unary functions.
    */
   namespace unary {

      /**
       * This metafunction composes a unary function from the supplied typelist
       * of functors.
       *
       * \tparam F A list of unary functors to compose. The functors will be
       *    applied in reverse order from the rightmost element of the list first
       *    to the leftmost element of the list last.
       *
       * \see typelist
       */
      template<typename F>
      struct map;
   }
}

/* implementations */
/*===========================================================================*/
/// \cond Allow doxygen to skip internal implementation details.
namespace type {
   
   struct true_tag {};
   struct false_tag {};

   template<typename T, typename U>
   struct eq {
      typedef false_tag type;
      static const bool value = false;
   };

   template<typename T>
   struct eq<T, T> {
      typedef true_tag type;
      static const bool value = true;
   };

   namespace qualifier {
     
      // type::qualifier::strip implementation
      /*=====================================================================*/
      template<typename T, typename U>
      struct strip { typedef T type; };

      template<typename T, typename U>
      struct strip<const T, const U> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T, const U> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<volatile T, volatile U> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T, volatile U> { typedef typename strip<T, U>::type type; };
      
      template<typename T, typename U>
      struct strip<const volatile T, const volatile U> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T, const volatile U> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T *, U *> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T, U *> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T const *, U const *> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T, U const *> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T * const, U * const> { typedef typename strip<T, U>::type type; };
      
      template<typename T, typename U>
      struct strip<T, U * const> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T &, U &> { typedef typename strip<T, U>::type type; };
      
      template<typename T, typename U>
      struct strip<T, U &> { typedef typename strip<T, U>::type type; };

      template<typename T, typename U>
      struct strip<T const &, U const &> { typedef typename strip<T, U>::type type; };
      
      template<typename T, typename U>
      struct strip<T, U const &> { typedef typename strip<T, U>::type type; };


      // type::qualifier::copy implemenatation
      /*=====================================================================*/
      template<typename T, typename U, typename V>
      struct copy { typedef U type; };

      template<typename T, typename U, typename V>
      struct copy<const T, U, const V> { typedef typename copy<T, const U, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<T, U, const V> { typedef typename copy<T, U, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<volatile T, U, volatile V> { typedef typename copy<T, volatile U, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T, U, volatile V> { typedef typename copy<T, U, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<const volatile T, U, const volatile V> { typedef typename copy<T, const volatile U, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<T, U, const volatile V> { typedef typename copy<T, U, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T *, U, V *> { typedef typename copy<T, U *, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T, U, V *> { typedef typename copy<T, U, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T const *, U, V const *> { typedef typename copy<T, U const *, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<T, U, V const *> { typedef typename copy<T, U, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T * const, U, V * const> { typedef typename copy<T, U * const, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<T, U, V * const> { typedef typename copy<T, U, V>::type type; };

      // \todo this should not be needed.
      template<typename T, typename U, typename V>
      struct copy<T const * const, U, V const * const> { typedef typename copy<T, U const * const, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<T, U, V const * const> { typedef typename copy<T, U, V>::type type; };
      // end unneeded

      template<typename T, typename U, typename V>
      struct copy<T &, U, V &> { typedef typename copy<T, U &, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T, U, V &> { typedef typename copy<T, U, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<T &, U &, V &> { typedef typename copy<T, U &, V>::type type; };
      
      template<typename T, typename U, typename V>
      struct copy<T, U &, V &> { typedef typename copy<T, U &, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T const &, U, V const &> { typedef typename copy<T, U const &, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T, U, V const &> { typedef typename copy<T, U, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T const &, U const &, V const &> { typedef typename copy<T, U const &, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T, U const &, V const &> { typedef typename copy<T, U const &, V>::type type; };

      template<typename T, typename U, typename V>
      struct copy<T const &, U &, V const &> { typedef typename copy<T, U const &, V>::type type; };
   }
}

/**
 * Typelist functions
 */
namespace typelist {
   struct nil {};
   
   template<typename H, typename T>
   struct cons {
      typedef H head;
      typedef T tail;
   };

   template<typename list>
   struct last {
      typedef typename last2<typename list::head, typename list::tail>::type type;
   };

   template<>
   struct last<nil> {
      typedef nil type;
   };

   template<typename head, typename tail>
   struct last2 {
      typedef typename last2<typename tail::head, typename tail::tail>::type type;
   };

   template<typename head>
   struct last2<head, nil> {
      typedef head type;
   };
}
/// \endcond

namespace function {

   using namespace typelist;
   
   //struct binary_tag {};
   //struct unary_tag {};
  
   /// \cond Let doxygen skip internal implementation details.
   namespace binary {

      /*
      template<typename A, typename B>
      true_tag is_related(const A* = static_cast<B*>(0));
      
      template<typename A, typename B>
      false_tag is_related(const void * = static_cast<B*>(0));
      */
     
      template<typename F1, typename F2, typename F3>
      struct map : private F1, private F2, private F3 {
         typedef typename F1::result_type result_type;
         typedef typename F2::argument_type first_argument_type;
         typedef typename F3::argument_type second_argument_type;
      
         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(F2::operator()(x), F3::operator()(y));
         }
      };

      template<typename F1, typename F2>
      struct map<F1, F2, F2> : private F1, private F2 {
         typedef typename F1::result_type result_type;
         typedef typename F2::argument_type first_argument_type;
         typedef typename F2::argument_type second_argument_type;

         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(F2::operator()(x), F2::operator()(y));
         }
      };
      
      template<typename F1, typename F3>
      struct map<F1, nil, F3> : private F1, private F3 {
         typedef typename F1::result_type result_type;
         typedef typename F1::first_argument_type first_argument_type;
         typedef typename F3::argument_type second_argument_type;
      
         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(x, F3::operator()(y));
         }
      };
      
      template<typename F1, typename F2>
      struct map<F1, F2, nil> : private F1, private F2 {
         typedef typename F1::result_type result_type;
         typedef typename F2::argument_type first_argument_type;
         typedef typename F1::second_argument_type second_argument_type;
      
         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(F2::operator()(x), y);
         }
      };
      
      template<typename F1>
      struct map<F1, nil, nil> : public F1 {
         typedef typename F1::result_type result_type;
         typedef typename F1::first_argument_type first_argument_type;
         typedef typename F1::second_argument_type second_argument_type;
         /* operator() inherited from F1 */ 
      };
   }
   /// \endcond
   
   namespace unary {
   
      using namespace typelist;

      /**
       * \struct function::unary::map
       *
       * General case. recursively builds a call chain from the supplied list
       * of functors.
       *
       * \par Example
       * \code
       *
       * // creates a list of 3 functors.
       * using typelist::cons;
       * typedef cons<f1, cons<f2, cons<f3> > mylist;
       * // creates the call chain: f1(f2(f3(x)));
       * typedef function::unary::map<mylist> f123;
       * // instantiate f123 and call.
       * f123 f_it;
       * f123::argument_type x = 23;
       * f123::result_type y = f_it(x);
       *
       * \endcode
       *
       * \tparam list A cons list (typelist::cons) of functors to chain 
       *    together as a composite function. Each functor in the list is 
       *    expected to supply type definitions for \c result_type and 
       *    \c argument_type.
       */
      /// \cond
      template<typename list>
      struct map : private virtual list::head, private map<typename list::tail> {
         typedef typename list::head::result_type result_type;
         typedef typename last<list>::type::argument_type argument_type;
   
         result_type operator()(argument_type x) {
            /* operator() inherited from head and tail */
            return list::head::operator()(map<typename list::tail>::operator()(x));
         }
      };
      /// \endcond
  
      /**
       * \struct function::unary::map
       *
       * Base case. simply forwards type declarations and exposes the public 
       * interface inherited from T.
       *
       * \tparam T The class to inherit from. T is expected to provide type
       *    definitions for \c result_type and \c argument_type.
       *
       * \note either virtual inheritance or a member variable must be used
       *    whenever the same functor is applied more than once in the call 
       *    chain.
       *
       * \todo is it possible to do this without virtual inheritance?
       */
      /// \cond
      template<typename T>
      struct map<cons<T, nil> > : public virtual T {
         typedef typename T::result_type result_type;
         typedef typename T::argument_type argument_type;
         /* operator() inherited from T */
      };
      /// \endcond
   }
}

#include <utility>
class Territory;

/**
 * \todo Should this namespace live in a separate file?
 */
namespace util {
   /// \cond Allow doxygen to skip implementation details.
   using function::unary_tag;

   template<typename T, typename U>
   struct dereference {
      typedef U* argument_type;
      typedef T& result_type;

      result_type operator()(argument_type t) const {
         return *t;
      }
   };

   template<typename T>
   struct delete_if : public T {
      typedef typename type::qualifier::strip<typename T::first_argument_type>::type * first_argument_type;
      typedef typename type::qualifier::strip<typename T::second_argument_type>::type * second_argument_type;
      typedef typename T::result_type result_type;

      result_type operator()(first_argument_type x, second_argument_type y) const {
         result_type result = T::operator()(*x, *y);
         
         if (static_cast<bool>(result))
            delete y;
         
         return result;
      }
   };

   // deprecated
   template<typename T, typename AttrT, AttrT (T::*Tattr)() const>
   struct member {
      typedef const T & argument_type;
      typedef AttrT result_type;

      result_type operator()(argument_type x) const {
         return (x.*Tattr)();
      }
   };
   /// \endcond
}

#endif /* TEMPLATE_FUNCTIONAL_H */

