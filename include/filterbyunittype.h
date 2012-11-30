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
/** \file filterbyunittype.h
 * Implementation file for FilterByUnitType class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef FILTERBYUNITTYPE_H
#define FILTERBYUNITTYPE_H

#include "unitoperation.h"

namespace game {
   class Unit;
}

/**
 * Implements the UnitOperation interface class, FilterByUnitType
 * will return true only if the FilterByUnitType::operator()(Unit *)
 * is passed the same type of unit object that was passed in the
 * constructor and false otherwise.
 */
class FilterByUnitType : public UnitOperation {
  public:

   //constructors

   /// \param u -- pointer to parent Unit
   //
   /// \post MIL:
   ///       <br>- sets unitType to u
   ///       <br>- sets fName to name of u
   FilterByUnitType(game::Unit * u);

   //destructor
   
   ~FilterByUnitType(){}
   
   //accessors

   /// \param unit -- pointer to Unit that compares to this parent Unit
   //
   /// \return bool, true if unit and parent Unit are same type
   bool operator()(game::Unit * unit) const;

   //! @copydoc UnitOperation::name()
   std::string name() const;
   
  private:
   game::Unit * unitType; ///< pointer to parent Unit
   std::string fName; ///< string, name of u
};

#endif
