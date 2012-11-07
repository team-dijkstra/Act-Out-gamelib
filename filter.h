#ifndef FILTER_H
#define FILTER_H

#include "filter.h"
#include <string>

class Unit;


class Filter {
  public:
   ~Filter(){}
   //mutators
   virtual bool operator()(Unit *) =0;
   //accessor
   virtual std::string name() =0;

};

#endif
