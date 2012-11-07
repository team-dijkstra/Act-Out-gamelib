#ifndef FILTERBYUNITTYPE_H
#define FILTERBYUNITTYPE_H

#include "filter.h"

class FilterByUnitType : public Filter {
  public:
   FilterByUnitType(Unit * u);
   ~FilterByUnitType(){}
   //mutators
   bool operator()(Unit *);

   //accessor
   std::string name();

  private:
   Unit * unitType;
   std::string fName;
};

#endif
