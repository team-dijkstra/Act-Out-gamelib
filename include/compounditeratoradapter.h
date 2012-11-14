
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
   typename CV //,
   //typename std::iterator_traits<CI>::value_type::* member = NULL
   > 
class CompoundIteratorAdapter {
  public:
   // Helper types 
   typedef CompoundIteratorAdapter<CI, CV> self_type;
   
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
      return (compound_iterator == rhs.val);
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

   /*
   reference operator* () const {
      return compound_iterator->*member;
   }

   pointer operator-> () const {
      return &(compound_iterator->*member);
   }
   */

  private:
   /// \todo Shouldn't need to store this since it should be a compile
   ///       time constant.
   //typename outer_value_type::* member;
   CI & compound_iterator;
};


#endif /* COMPOUND_ITERATOR_ADAPTER_H */

