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
/** \file filterbyterritoryownername.h
 * Implementation file for FilterByTerritoryOwnerName class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef FILTERBYTERRITORYUNIT_H
#define FILTERBYTERRITORYUNIT_H

#include "territoryoperation.h"

/**
 * Implements the TerritoryOperation interface class, FilterByTerritoryUnit
 * will return true only if the FilterByTerritoryUnit::operator()(Territory *)
 * is passed the same name of territory object that was passed in the
 * constructor and false otherwise.
 */
class FilterByTerritoryUnit : public TerritoryOperation {
  public:

   //constructors

   /// sets territoryUnit to t
   //
   /// \param t -- const string compared to comparing Territory unit name
   FilterByTerritoryUnit(const std::string & t);

   //destructor
   
   ~FilterByTerritoryUnit(){}
   
   //accessors

   /// \param t -- pointer to the Territory to check for the unit type the operation was constructed with. 
   //
   /// \return bool, true if t unit name and unitName are same
   bool operator()(Territory * t) const;

  private:
   const std::string unitName; ///< const string of unit name
};

#endif