#ifndef PHASE_H
#define PHASE_H

#include <string>

class Phase{
  public:
   virtual ~Phase() {}
   virtual std::string name() const =0;
};

#endif
