/// \file
/// \brief Interface file for the game units -- unit.h
//
/// Specified behaviour of game units

#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

class Territory;
class Action;

///An interface to specify the behaviour of the game units
class Unit {
  public:
   virtual ~Unit() {}

   //mutators
   /// Increases the numUnits in this Unit
   //
   /// \param a Unit object
   //
   /// \post increases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after increase
   ///         method is performed
   virtual int increase (Unit* u) =0;

   /// Decreases the numUnits in this Unit
   //
   /// \param a Unit object
   //
   /// \post decreases the numUnits in this object by the
   ///       numUnits in the passed object.
   /// \return the current numUnits in this object after decrease
   ///         method is performed
   virtual int decrease (Unit* u) =0;

   //accessors
   /// \return the current numUnits in this object
   virtual int numUnits() const =0;

   /// \return the Territory where this Unit is located
   virtual Territory* whereAt() const =0;

   /// \return the type name of this object
   virtual std::string name() const =0;

   /// \return all the possible actions that this unit can perform
   virtual std::vector<Action*> actions() const =0;
   
};

#endif
