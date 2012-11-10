/// \file
/// \brief Interface file for the game units -- unit.h
//
/// Specified behaviour of game units

#ifndef TRADITIONAL_ARMY_H
#define TRADITIONAL_ARMY_H

#include "unit.h"

///An interface to specify the behaviour of the game units
class TraditionalArmy : public Unit {
  public:
  TraditionalArmy(int, Territory * );
   ~TraditionalArmy() {}

   //mutators
   /// Increases the numUnits in this Unit
   //
   /// \param a Unit object
   //
   /// \post increases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after increase
   ///         method is performed
   int increase (Unit* u);

   /// Decreases the numUnits in this Unit
   //
   /// \param a Unit object
   //
   /// \post decreases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after decrease
   ///         method is performed
   int decrease (Unit* u);

   //accessors
   /// \return the current numUnits in this object
   int numUnits() const;

   /// \return the Territory where this Unit is located
   Territory* whereAt() const;

   /// \return the type name of this object
   std::string name() const;

   /// \return all the possible actions that this unit can perform
   std::vector<Action*> actions() const;

  private:
   int nUnits;
   Territory * uTerritory;
   std::string uName;
   std::vector<Action*> uActions;
   
};

#endif
