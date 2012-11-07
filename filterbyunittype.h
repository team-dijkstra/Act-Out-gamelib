#ifndef FILTERBYUNITTYPE_H
#define FILTERBYUNITTYPE_H

#include "filter.h"

class FilterByUnitType : public Filter {
  public:
   FilterByUnitType(Unit * u);
   ~FilterByUnitType(){}
   //accessor
   std::string name() const;
   bool operator()(Unit *) const;
   
  private:
   Unit * unitType;
   std::string fName;
};

#endif
