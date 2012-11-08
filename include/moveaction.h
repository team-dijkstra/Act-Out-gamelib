/// \file
/// \brief contains the interface class Action -- action.h
//
/// MoveAction class interface, specifies behavious of game actions

#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <string>
#include "territory.h"
#include "phase.h"
//class Territory;
//class Phase;

///Basic interface specifying behaviour for class Action
//
///MoveAction move numUnits from one Territory to another
template<typename U>
class MoveAction : public Action{
  public:
   ~MoveAction() {}
	     
   //accessors
   /// \return the name of the action class
   std::string name() const
   {
      return "MoveAction";
   }

   /// \return true if action can be used in the specified Phase; false otherwise
   bool applicable(Phase* p) const
   {
      return (p->name() == "Redeploy");
   }
   
   //mutators
   /// \param nUnits  -- the number of units to commit to current action
   /// \param T -- the territory to act on.
   //
   /// \post preforms Action on the specified territory using specifiec number of units
   void doaction(int nUnits, Territory * T)
   {
      // do stuff here
   }
   

  private:
   U * parent;
};

#endif
