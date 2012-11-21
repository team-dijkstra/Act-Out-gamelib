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
 */

#ifndef TEMPLATE_FUNCTIONAL_H
#define TEMPLATE_FUNCTIONAL_H

//#include <functional>

namespace util {

   template<typename T>
   class Dereference
   //: public std::unary_function<const T *, const T &>
   {
     public:
      typedef const T* argument_type;
      typedef const T& result_type;

      result_type operator()(argument_type t) {
         return *t;
      }
   };

}

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
}

/**
 * Typelist functions
 */
namespace typelist {
   struct nil {};
   
   template<typename H, typename T = nil>
   struct cons;

   template<typename head, typename tail = nil>
   struct last2;

   template<typename list = nil>
   struct last;

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

namespace function {

   using namespace typelist;
   
   struct binary_tag {};
   struct unary_tag {};
   
   namespace binary {

      template<typename F1, typename F2 = nil, typename F3 = nil>
      struct map;

      /*
      template<typename A, typename B>
      true_tag is_related(const A* = static_cast<B*>(0));
      
      template<typename A, typename B>
      false_tag is_related(const void * = static_cast<B*>(0));
      */
      
      template<typename F1, typename F2, typename F3>
      struct map : public binary_tag, F1, F2, F3 {
         typedef typename F1::result_type result_type;
         typedef typename F2::argument_type first_argument_type;
         typedef typename F3::argument_type second_argument_type;
      
         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(F2::operator()(x), F3::operator()(y));
         }
      };
      
      template<typename F1, typename F3>
      struct map<F1, nil, F3> : public binary_tag, F1, F3 {
         typedef typename F1::result_type result_type;
         typedef typename F1::first_argument_type first_argument_type;
         typedef typename F3::argument_type second_argument_type;
      
         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(x, F3::operator()(y));
         }
      };
      
      template<typename F1, typename F2>
      struct map<F1, F2, nil> : public binary_tag, F1, F2 {
         typedef typename F1::result_type result_type;
         typedef typename F2::argument_type first_argument_type;
         typedef typename F1::second_argument_type second_argument_type;
      
         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(F2::operator()(x), y);
         }
      };
      
      template<typename F1>
      struct map<F1, nil, nil> : public binary_tag, F1 {
         typedef typename F1::result_type result_type;
         typedef typename F1::first_argument_type first_argument_type;
         typedef typename F1::second_argument_type second_argument_type;
      
         result_type operator()(first_argument_type x, second_argument_type y) {
            return F1::operator()(x, y);
         }
      };
   }
   
   namespace unary {
   
      namespace v1 {
         using typelist::last;
   
         template<typename F1, typename F2 = nil>
         struct map;
   
         template<typename F1, typename F2>
         struct map : public unary_tag, F1, map<typename F2::head, typename F2::tail> {
            typedef F1 head;
            typedef F2 tail;
            typedef typename F1::result_type result_type;
            typedef typename last<F2>::type::argument_type argument_type;
   
            result_type operator()(argument_type x) {
               /* operator() inherited from head and tail */
               return F1::operator()(map<typename tail::head, typename tail::tail>::operator()(x));
            }
         };
   
         template<typename F1>
         struct map<F1, nil> : public unary_tag, public F1 {
            typedef F1 head;
            typedef nil tail;
            typedef typename F1::result_type result_type;
            typedef typename F1::argument_type argument_type;
         };
   
      }
   
      using namespace typelist;
   
      template<typename>
      struct map;
   
      template<typename list>
      struct map : public unary_tag,  list::head, map<typename list::tail> {
         typedef typename list::head::result_type result_type;
         typedef typename last<list>::head::argument_type argument_type;
   
         result_type operator()(argument_type x) {
            /* operator() inherited from head and tail */
            return list::head::operator()(map<typename list::tail>::operator()(x));
         }
      };
   
      template<typename T>
      struct map<cons<T, nil> > : public unary_tag, T {
         typedef typename T::result_type result_type;
         typedef typename T::argument_type argument_type;
         /* operator() inherited from T */
      };
   }
}

/*
map<std::less, map<std::less, Dereference, Dereference> >

map<list<negate, list<transform, list<map<std::less, Dereference, Dereference> > > >
*/

#endif /* TEMPLATE_FUNCTIONAL_H */

