
#ifndef TRIVIAL_TERRITORY_FILTER_H
#define TRIVIAL_TERRITORY_FILTER_H

#include <vector>
#include "territory.h"
#include "territoryoperation.h"

class TerritoryPassFilter : public TerritoryOperation {
  public:
   bool operator()(Territory * t);
};

class TerritoryBlockFilter : public TerritoryOperation {
  public:
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
   }

  private:
   C names; 
};

#endif /* TRIVIAL_TERRITORY_FILTER_H */

