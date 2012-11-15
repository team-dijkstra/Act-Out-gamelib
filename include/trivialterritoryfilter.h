
#ifndef TRIVIAL_TERRITORY_FILTER_H
#define TRIVIAL_TERRITORY_FILTER_H

#include "territoryoperation.h"

class TerritoryPassFilter : public TerritoryOperation {
  public:
   bool operator()(Territory * t);
};

class TerritoryBlockFilter : public TerritoryOperation {
  public:
   bool operator() (Territory * t);
};

#endif /* TRIVIAL_TERRITORY_FILTER_H */

