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
 * \file compare.h
 * 
 * contains implementations of comparators based on arbitrary pairs of 
 * member functions of the supplied types.
 *
 * \deprecated
 */

#ifndef COMPARE_H
#define COMPARE_H

/**
 * A class template wrapper that allows any two arbitrary objects to be
 * compared by any pair of attributes, so long as comparison is defined
 * for the two attribute types. Each attribute is expected to be exposed
 * as an accessible const member function taking taking 0 arguments.
 * 
 * \tparam L The type of the left hand side comparison object.
 * \tparam AttrL The type of the left hand side object attribute under
 *    comparison.
 * \tparam Lattr A pointer to a member function of L accepting 0 arguments,
 *    and returning an AttrL value.
 * \tparam R The type of the right hand side comparison object. Defaults to L.
 * \tparam AttrR The type of the right hand side object attribute under
 *    comparison. defaults to AttrL.
 * \tparam Rattr A pointer to a member function of R accepting 0 arguments,
 *    and returning an AttrR value. defaults to Lattr.
 */
template<
   typename L, 
   typename AttrL, 
   AttrL (L::*Lattr)() const, 
   typename R = L, 
   typename AttrR = AttrL, 
   AttrR (R::*Rattr)() const = Lattr>
class Compare {
    typedef Compare<L, AttrL, Lattr, R, AttrR, Rattr> self_type;
    typedef Compare<L, AttrL, Lattr> left_type;
    typedef Compare<R, AttrR, Rattr> right_type;
    typedef L value_type;
  public:

   /**
    * Conversion constructor. Accepts an instance of the underlying type of the
    * left hand comparison object.
    * 
    * \param _lhs An instance of the object to be used on the left hand side
    *    of the comparison.
    */
   Compare(const value_type & _lhs) : lhs(_lhs) {}
   Compare(const value_type * _lhs) : lhs(*_lhs) {}
   
   /**
    * Less than operator to compare objects by attribute pair.
    *
    * \param rhs The right hand side operand.
    *
    * \return true if \begincode lhs.Lattr() < rhs.Rattr() \endcode. false otherwise.
    */
   bool operator< (const right_type & rhs) const {
      return attr(*this) < attr(rhs);
   }

   /**
    * Equality operator to compare objects by attribute pair.
    *
    * \param rhs The right hand side operand.
    *
    * \return true if \begincode lhs.Lattr() == rhs.Rattr() \endcode. false
    *    otherwise.
    */
   bool operator== (const right_type & rhs) const {
      return attr(*this) == attr(rhs);
   }

   /**
    * Less than or equal comparison operator. Implemented in terms of 
    * operator< and operator==.
    * 
    * \see operator<
    * \see operator==
    */
   bool operator<= (const right_type & rhs) const {
      return ((*this < rhs) || (*this == rhs));
   }
   /**
    * Greater than comparison operator. Implemented in terms of 
    * operator< and operator==.
    * 
    * \see operator<
    * \see operator==
    */
   bool operator> (const right_type & rhs) const {
      return !(*this <= rhs);
   }

   /**
    * Greater than or equal comparison operator. Implemented in terms of 
    * operator< and operator==.
    * 
    * \see operator<
    * \see operator==
    */
   bool operator>= (const right_type & rhs) const {
      return ((*this == rhs) || (*this > rhs));
   }

  private:
   /**
    * Convenience accessor to make access more uniform. 
    * 
    * \todo Candidate for extraction to a policy class.
    */
   template<typename T, typename AttrT, AttrT (T::*Tattr)() const>
   const AttrT attr(const Compare<T, AttrT, Tattr> & item) const {
      return ((item.lhs).*Tattr)();
   }

   const value_type & lhs;
};

#endif /* COMPARE_H */
