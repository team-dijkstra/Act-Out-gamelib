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
/** \file filterbyterritoryowner.h
 * Implementation file for FilterByTerritoryOwner class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef FILTERBYTERRITORYOWNER_H
#define FILTERBYTERRITORYOWNER_H

#include "territoryoperation.h"

namespace game {
   class Territory;
}

/**
 * Implements the TerritoryOperation interface class, FilterByTerritoryOwner
 * will return true only if the FilterByTerritoryOwner::operator()(Territory *)
 * is passed the same name of territory object that was passed in the
 * constructor and false otherwise.
 */
class FilterByTerritoryOwner : public TerritoryOperation {
  public:

   //constructors

   /// sets territoryOwner to t
   //
   /// \param t -- const string compared to comparing Territory owner name
   FilterByTerritoryOwner(const std::string & t);

   //destructor
   
   ~FilterByTerritoryOwner(){}
   
   //accessors

   /// \param t -- pointer to Territory that compares to territoryOwner
   //
   /// \return bool, true if t owner name and territoryOwner are same
   bool operator()(game::Territory * t);

  private:
   const std::string territoryOwner; ///< const string of Territory owner name
};

#endif
