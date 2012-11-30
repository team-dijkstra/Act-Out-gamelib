
#ifndef REMOVE_OWNER_H
#define REMOVE_OWNER_H

#include <string>
#include <algorithm>
#include "territoryoperation.h"

namespace game {
   class Territory;
}

/// Removes the names from the supplied list that correspond to territories
/// owned by the specified owner.
template<typename C>
class RemoveOwnedBy : public TerritoryOperation {
  public:
   RemoveOwnedBy(const std::string & nm, const C & c) : pName(nm), remaining(c) {}

   bool operator()(game::Territory * t) {
      if (t->owner()->name() == pName) {
         typename C::iterator pos = std::find(remaining.begin(), remaining.end(), t->name());
         if (remaining.end() != pos) remaining.erase(pos);
      }

      return false;
   }

   C result() {
      return remaining;
   }

  private:
   std::string pName;
   C remaining;
};

#endif /* REMOVE_OWNER_H */

