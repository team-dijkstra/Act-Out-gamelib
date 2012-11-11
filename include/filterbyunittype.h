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
#ifndef FILTERBYUNITTYPE_H
#define FILTERBYUNITTYPE_H

#include "filter.h"

class FilterByUnitType : public Filter {
  public:
   FilterByUnitType(Unit * u);
   ~FilterByUnitType(){}
   //accessor
   std::string name() const;
   bool operator()(Unit *) const;
   
  private:
   Unit * unitType;
   std::string fName;
};

#endif
