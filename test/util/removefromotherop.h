
#ifndef REMOVE_FROM_OTHER_H
#define REMOVE_FROM_OTHER_H

#include <vector>
#include <algorithm>
#include "territoryoperation.h"

/// Removeal filter that implements an UnBuilder Pattern.
///
/// \tparam C The container type of 'other'.
///
template<typename C>
class RemoveFromOther : public TerritoryOperation {
  public:
   /// Constructor.
   ///
   /// \param o The other set container to remove elements from.
   ///      Matches are performed by name.
   RemoveFromOther(const C & o) : other(o) {}

   bool operator()(Territory * t) {
      typename C::iterator pos;
      pos = std::find(other.begin(), other.end(), t->name());
      if (other.end() != pos) other.erase(pos);
   }

   /// Allows the resulting set to be retrieved once all operations have
   /// been performed on it.
   ///
   /// \return the resulting set.
   C result() {
      return other;
   }

  private:
   C other;
};

#endif /* REMOVE_FROM_OTHER_H */

