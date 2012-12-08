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
/** \file filterbyterritoryname.h
 * Implementation file for FilterByTerritoryName class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef FILTERBYTERRITORYNAME_H
#define FILTERBYTERRITORYNAME_H

#include "territoryoperation.h"

/**
 * Implements the TerritoryOperation interface class, FilterByTerritoryName
 * will return true only if the FilterByTerritoryName::operator()(Territory *)
 * is passed the same name of territory object that was passed in the
 * constructor and false otherwise.
 */
class FilterByTerritoryName : public TerritoryOperation {
  public:

   //constructors

   /// \param t -- const string compared to comparing Territory name
   ///
   /// sets territoryName to t
   FilterByTerritoryName(const std::string & t);

   //destructor
   
   ~FilterByTerritoryName(){}
   
   //accessors

   /// \param t -- the Territory to compare by name with the constructor
   /// supplied string.
   ///
   /// \return true if \c t->name() and the \c territoryName this functor was
   /// constructed with are same. false otherwise
   bool operator()(Territory * t);

  private:
   const std::string territoryName; ///< the territory name to use in comparison
};

#endif
