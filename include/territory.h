/// \file
/// \brief contains interface class Territory -- territory.h
//
/// Territory interface class
#ifndef TERRITORY_H
#define TERRITORY_H

#include <string>
#include <vector>
#include <map>

class Player;
class Filter;
class Unit;

/// An interface class to represent a Territory 
class Territory {
  public:

   typedef std::map<std::string, Unit*> unitContainer;
   
   virtual ~Territory() {}

   //accessors
   /// \return the Player object that currently owns this Territory
   virtual Player* owner() const =0;
   
   /// \return a string, the name of the Territory
   virtual std::string name() const =0;

   /// \param[in] 
   /// \return a vector of Units that are on this Territory 
   virtual unitContainer units(Filter* f) const =0;

   //mutators
   /// \param[in] reference to Player object 
   /// \post sets Territory owner to the passed Player object
   virtual void owner(Player*) =0;
   virtual void addUnit(Unit*) =0;
};

#endif
