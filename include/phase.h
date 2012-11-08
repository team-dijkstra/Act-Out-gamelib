/// \file
/// \brief phase.h contains the interface class Phase -- phase.h
//
/// Phase class, a simple interface class to track the different game phases

#ifndef PHASE_H
#define PHASE_H

#include <string>

/// An interface class to represent the different game phases
class Phase{
  public:
   virtual ~Phase() {}

   //accessor
   /// \returns the name of the Phase
   virtual std::string name() const =0;
};

#endif
