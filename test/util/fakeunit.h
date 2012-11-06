/// \file
/// \brief Interface file for the game units -- unit.h
//
/// Specified behaviour of game units

#ifndef FAKEUNIT_H
#define FAKEUNIT_H

#include "unit.h"

class Territory;
class Action;

///An interface to specify the behaviour of the game units
class FakeUnit {
  public:
   FakeUnit(int nunit, Territory * t, std::vector<Action*> uActs);
   ~FakeUnit() {}

   //mutators
   /// Increases the numUnits in this FakeUnit
   //
   /// \param a Unit object
   //
   /// \post increases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after increase
   ///         method is performed
   int increase (Unit* u);

   /// Decreases the numUnits in this FakeUnit
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

   /// \return the Territory where this FakeUnit is located
   Territory* whereAt() const;

   /// \return the type name of this object
   std::string name() const;

   /// \return all the possible actions that this unit can perform
   std::vector<Action*> actions() const;

  private:
   int nUnits;
   Territory * tWhere;
   std::string uName;
   std::vector<Action*> uActions;
   
   
};

#endif
