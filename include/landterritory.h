/*
Act-Out! game library - implements generic game logic.
Copyright (C) 2012 Rio Lowry, Chris Pinter, Matt Voroney

This file is part of Act-Out!

Act-Out! is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Act-Out! is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Act-Out!.  If not, see <http://www.gnu.org/licenses/>.
*/
/// \file
/// \brief contains interface class Territory -- territory.h
//
/// Territory interface class
#ifndef LAND_TERRITORY_H
#define LAND_TERRITORY_H

#include <map>
#include "territory.h"

/// An interface class to represent a Territory 
class LandTerritory : public Territory{
  public:

   //constructors

   /// \param nm -- string to be this Territory's name
   /// \param own -- pointer to Player to be owner
   ///
   /// \details sets tName to nm, sets tOwner to own
   /// \todo should own default to NULL?
   LandTerritory(std::string nm, Player * own = NULL);

   //destructor

   ///Destructor. Deletes its units.
   ~LandTerritory();

   //accessors
   
   //! @copydoc Territory::owner()
   Player* owner() const;
   
   //! @copydoc Territory::name()
   std::string name() const;

   //! @copydoc Territory::units()
   unitContainer units(UnitOperation* f) const;

   //mutators
   
   //! @copydoc Territory::owner(Player*)
   void owner(Player * p);

   //! @copydoc Territory::addUnit()
   void addUnit(Unit * u);

  private:
   
   std::string tName; ///< string, name of Territory
   Player * tOwner; ///< pointer to Player that is owner of this Territory
   unitContainer tUnits; ///< unitContainer of Units on this Territory
   
};

#endif
