#ifndef FILTERBYALLUNITTYPES_H
#define FILTERBYALLUNITTYPES_H

#include "filter.h"


class FilterByAllUnitTypes : public Filter {
  public:
   FilterByAllUnitTypes(Unit *);
   ~FilterByAllUnitTypes(){}
   //mutators
   bool operator()(Unit *);
   std::string name();

  private:
   std::string fName;
   Unit * unitType;
};

#endif
