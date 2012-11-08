#ifndef CONCRETE_PHASE_H
#define CONCRETE_PHASE_H

#include "phase.h"

class ConcretePhase : public Phase{
  public:
   ConcretePhase(const std::string & nm);
   ~ConcretePhase() {}

   //accessor
   /// \returns the name of the Phase
   virtual std::string name() const;

  private:
   std::string phasename;
};

#endif
