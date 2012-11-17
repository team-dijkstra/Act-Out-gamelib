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
/** \file unitoperation.h
 * Implementation file for UnitOperation class
 */
#ifndef UNITOPERATION_H
#define UNITOPERATION_H

#include <string>

class Unit;

/**
 * This is an interface class that defines a filtering functor class,
 * unit operations will define a set of units and return true if the
 * passed unit belongs in the set, false otherwise.
 */
class UnitOperation {
  public:

   //destructor
   
   ~UnitOperation(){}
   
   //accessors

   /// \param unit -- pointer to Unit that compares to this parent Unit
   //
   /// \return bool, true if unit and parent Unit are same type
   virtual bool operator()(Unit * unit) const =0;

   /// \return string, name of parent Unit
   virtual std::string name() const =0;
};

#endif
