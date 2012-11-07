#ifndef FILTERBYALLUNITTYPES_H
#define FILTERBYALLUNITTYPES_H

#include "filter.h"


class FilterByAllUnitTypes : public Filter {
  public:
   FilterByAllUnitTypes(Unit *);
   ~FilterByAllUnitTypes(){}
   //accessors
   bool operator()(Unit *) const;
   std::string name() const;

  private:
   std::string fName;
   Unit * unitType;
};

#endif
