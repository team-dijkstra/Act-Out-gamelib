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
/** \file filterbyallunittypes.h
 * Implementation file for FilterByAllUnitTypes class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef FILTERBYALLUNITTYPES_H
#define FILTERBYALLUNITTYPES_H

#include "unitoperation.h"

/**
 * Implements the UnitOperation interface class, FilterByAllUnitTypes
 * will return true for any unit passed.
 */
class FilterByAllUnitTypes : public UnitOperation {
  public:

   //constructors
   
   /// \param u -- pointer to parent Unit
   //
   /// \post MIL:
   ///       <br>- sets unitType to u
   ///       <br>- sets fName to "AllUnits"
   FilterByAllUnitTypes(Unit * u = NULL);
   
   //destructor
   
   ~FilterByAllUnitTypes(){}
   
   //accessors

   /// \param unit -- pointer to Unit that compares to this parent Unit
   //
   /// \return bool, always true
   bool operator()(Unit *) const;

   //! @copydoc UnitOperation::name()
   std::string name() const;

  private:

   
   std::string fName; //! @copydoc FilterByUnitType::fName
   
};

#endif
