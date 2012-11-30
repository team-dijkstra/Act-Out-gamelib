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
 * \file namecomparators.h
 * 
 * contains implementations of comparators based on a 'name' member function
 * of the supplied types.
 *
 */

#ifndef NAME_COMPARATORS_H
#define NAME_COMPARATORS_H

/**
 * \namespace compare
 *
 * Supplies comparison methods.
 */
namespace game {
   /**
    * \namespace compare::byname
    *
    * Supplies comparison methods that operate on a 'name()' member.
    * 
    * \todo it should be possible to reuse some of these operator definitions
    *    since they are given purely in terms of < and ==.
    */
      
      /**
       * Less than operator to compare objects by name.
       *
       * \tparam T the type of the objects to compare. T must supply a 'name()' 
       *    method that takes no arguments and returns a std::string.
       *
       * \param lhs The left hand side operand.
       * \param rhs The right hand side operand.
       *
       * \return true if \begincode lhs.name() < rhs.name() \endcode. false otherwise.
       */
      template<typename T>
      bool operator< (const T & lhs, const T & rhs) {
         return (lhs.name() < rhs.name());
      }

      /**
       * Equality operator to compare objects by name.
       *
       * \tparam T the type of the objects to compare. T must supply a 'name()'
       *    method that takes no arguments and returns a std::string.
       *
       * \param lhs The left hand side operand.
       * \param rhs The right hand side operand.
       *
       * \return true if \begincode lhs.name() == rhs.name() \endcode. false
       *    otherwise.
       */
      template<typename T>
      bool operator== (const T & lhs, const T & rhs) {
         return (lhs.name() == rhs.name());
      }

      /**
       * Less than or equal comparison operator. Implemented in terms of 
       * operator< and operator==.
       * 
       * \see operator<
       * \see operator==
       */
      template<typename T>
      bool operator<= (const T & lhs, const T & rhs) {
         return ((lhs < rhs) || (lhs == rhs));
      }
      /**
       * Greater than comparison operator. Implemented in terms of 
       * operator< and operator==.
       * 
       * \see operator<
       * \see operator==
       */
      template<typename T>
      bool operator> (const T & lhs, const T & rhs) {
         return !(lhs <= rhs);
      }

      /**
       * Greater than or equal comparison operator. Implemented in terms of 
       * operator< and operator==.
       * 
       * \see operator<
       * \see operator==
       */
      template<typename T>
      bool operator>= (const T & lhs, const T & rhs) {
         return ((lhs == rhs) || (lhs > rhs));
      }
}

#endif /* NAME_COMPARATORS_H */
