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
 * \file trivialterritoryfilter.h
 *
 * Experimental
 */

#ifndef TRIVIAL_TERRITORY_FILTER_H
#define TRIVIAL_TERRITORY_FILTER_H

#include <vector>
#include "territory.h"
#include "territoryoperation.h"

/// always returns true
class TerritoryPassFilter : public TerritoryOperation {
  public:
   ///\return always true
   bool operator()(Territory * t);
};

/// always returns false
class TerritoryBlockFilter : public TerritoryOperation {
  public:
   ///\return always false
   bool operator()(Territory * t);
};

/// Selects the set of territories match one of the supplied names.
   ///
/// \tparam C a container containing names to filter by.
   ///
template<typename C>
class TerritoryNameFilter: public TerritoryOperation {
  public:
   TerritoryNameFilter(const C & nms) : names(nms) {}
   
   bool operator()(Territory * t) {
      typename C::iterator it = names.begin();
      bool bfound = false;
      
      while (!bfound && it != names.end()) {
         bfound = (*it == t->name());
         it++;
      }

      return bfound;
   }

  private:
   C names; 
};

#endif /* TRIVIAL_TERRITORY_FILTER_H */

