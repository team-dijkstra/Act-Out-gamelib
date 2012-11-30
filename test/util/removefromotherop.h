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

   bool operator()(game::Territory * t) {
      typename C::iterator pos;
      pos = std::find(other.begin(), other.end(), t->name());
      if (other.end() != pos) other.erase(pos);

      return false;
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

