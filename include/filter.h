#ifndef FILTER_H
#define FILTER_H

#include "filter.h"
#include <string>

class Unit;


class Filter {
  public:
   ~Filter(){}
   //accessor
   virtual bool operator()(Unit *) const =0;
   virtual std::string name() const =0;

};

#endif
