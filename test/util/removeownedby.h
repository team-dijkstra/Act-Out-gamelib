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

