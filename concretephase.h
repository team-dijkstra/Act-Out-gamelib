#ifndef CONCRETE_PHASE_H
#define CONCRETE_PHASE_H

#include "phase.h"

class Phase{
  public:
   Phase(std::string name);
   ~Phase() {}

   //accessor
   /// \returns the name of the Phase
   virtual std::string name() const =0;

  private:
   std::string name;
};
