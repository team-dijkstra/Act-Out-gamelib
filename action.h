/// \file
/// \brief contains the interface class Action -- action.h
//
/// Action class interface, specifies behavious of game actions

#ifndef ACTION_H
#define ACTION_H

#include <string>

class Territory;
class Phase;

///Basic interface specifying behaviour for class Action
//
///Actions mutate game state.
class Action {
  public:
   virtual ~Action() {}

   //accessors
   /// \return the name of the action class
   virtual std::string name() const =0;

   /// \return true if action can be used in the specified Phase; false otherwise
   virtual bool applicable(Phase* p) const =0;

   //mutators
   /// \param nUnits  -- the number of units to commit to current action
   /// \param T -- the territory to act on.
   //
   /// \post preforms Action on the specified territory using specifiec number of units
   virtual void do(int nUnits,Territory* T) =0;
    
};

#endif
