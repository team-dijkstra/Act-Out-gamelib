/// \file
/// \brief contains interface class Territory -- territory.h
//
/// Territory interface class
#ifndef FAKETERRITORY_H
#define FAKETERRITORY_H
						\
#include "territory.h"
//class Player;
//class Unit;

/// An interface class to represent a Territory 
class FakeTerritory : public Territory{
  public:
  FakeTerritory(std::string & n, Player * own = NULL):tName(n), tOwner(own){}
   ~FakeTerritory() {}

   //accessors
   /// \return the Player object that currently owns this Territory
   Player* owner() const{}
   
   /// \return a string, the name of the Territory
   std::string name() const{ return tName;}

   /// \param[in] 
   /// \return a vector of Units that are on this Territory 
   std::vector<Unit*> units(Filter* f) const{}

   //mutators
   /// \param[in] reference to Player object 
   /// \post sets Territory owner to the passed Player object
   void owner(Player*){}

  private:
   std::string tName;
   Player * tOwner;
   
};

#endif
