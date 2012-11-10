/// \file
/// \brief contains interface class Territory -- territory.h
//
/// Territory interface class
#ifndef LAND_TERRITORY_H
#define LAND_TERRITORY_H

#include "territory.h"

/// An interface class to represent a Territory 
class LandTerritory : public Territory{
  public:
   LandTerritory(std::string nm, Player* own);
   ~LandTerritory() {}

   //accessors
   /// \return the Player object that currently owns this Territory
   Player* owner() const;
   
   /// \return a string, the name of the Territory
   std::string name() const;

   /// \param[in] 
   /// \return a vector of Units that are on this Territory 
   std::vector<Unit*> units(Filter* f) const;

   //mutators
   /// \param[in] reference to Player object 
   /// \post sets Territory owner to the passed Player object
   void owner(Player*);

  private:
   
   std::string tName;
   Player * tOwner;
   std::vector<Unit*> tUnits;
   
};

#endif
