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
/** \file filterbyallunittypes.cc 
 * Implementation file for FilterByAllUnitTypes class
 * Detatailed descriptions of each method are in the header file
 */
#include "filterbyallunittypes.h"
#include "unit.h"

FilterByAllUnitTypes::FilterByAllUnitTypes( Unit *) : fName("AllUnits")
{
}

FilterByAllUnitTypes::FilterByAllUnitTypes() {}

bool FilterByAllUnitTypes::operator()(Unit * unit) const
{
   return true;
}

std::string FilterByAllUnitTypes::name() const
{
   return fName;
}

