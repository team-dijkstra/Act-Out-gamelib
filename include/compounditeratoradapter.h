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

#ifndef COMPOUND_ITERATOR_ADAPTER_H
#define COMPOUND_ITERATOR_ADAPTER_H

#include <utility>
#include <iterator>

/// \class CompoundIteratorAdapter
///
/// Wrapper class that allows iteration over single field of compound type
/// such as a class, struct or union stored in the underlying container.
///
/// \tparam CI The underlying compound iterator exposed by the underlying
///         container type.
/// \tparam CV The component value type of the field to iterate over.
/// \tparam member A pointer to member for the field to iterate over.
///
/// \author Matt Voroney
///
/// \todo It should be possible to pass a pointer to member as a template
///       value parameter, but g++ seems to bail on this.
/// \todo It should be possible to extract the type of the pointer to member
///       field directly.
///
template<
   typename CI, 
   typename CV,
   CV std::iterator_traits<CI>::value_type::* member> 
class CompoundIteratorAdapter {
  public:
   // Helper types 
   typedef CompoundIteratorAdapter<CI, CV, member> self_type;
   
   // Iterator Traits
   typedef typename std::iterator_traits<CI>::difference_type difference_type;
   typedef typename std::iterator_traits<CI>::iterator_category iterator_category;
   typedef CV value_type;
   typedef CV* pointer;
   typedef CV& reference;
   typedef typename std::iterator_traits<CI>::value_type outer_value_type;

   CompoundIteratorAdapter(
      CI & ci //, 
   //   const outer_value_type::* mem
   ) : compound_iterator(ci)
   //, member(mem) 
   {}
   CompoundIteratorAdapter(self_type & ci) : compound_iterator(ci.compound_iterator) {}
   
   bool operator== (self_type const& rhs) const {
      return (compound_iterator == rhs.compound_iterator);
   }

   bool operator!= (self_type const& rhs) const {
      return !(*this == rhs);
   }

   self_type& operator++() {
      ++compound_iterator;
      return *this;
   }   

   self_type operator++(int) {
      self_type tmp(*this);
      ++(*this);
      return tmp;
   }

   self_type& operator--() {
      --compound_iterator;
      return *this;
   }

   self_type operator--(int) {
      self_type tmp(*this);
      --(*this);
      return tmp;
   }

   /**
    * \todo type mismatches.
   reference operator* () const {
      return compound_iterator.*member;
   }

   pointer operator-> () const {
      return &(compound_iterator->*member);
   }
   */

  private:
   CI & compound_iterator;
};


#endif /* COMPOUND_ITERATOR_ADAPTER_H */

