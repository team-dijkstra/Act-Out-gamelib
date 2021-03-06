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
/** \file territoryoperation.h
 * Implementation file for TerritoryOperation class
 * Detatailed descriptions of each method are in the header file
 */
#ifndef TERRITORYOPERATION_H
#define TERRITORYOPERATION_H

class Territory;
/**
 * This is a interface class that defines a filtering functor class,
 * territory operations will define a characteristic function of a set
 * of territories and return true if the passed territory belongs in
 * the set, false otherwise.
 *
 * If the operation does not define a characteristic function, but
 * instead applies some transformation to the supplied Territory,
 * then this should be indicated. In this case the return value should
 * always be false.
 */
class TerritoryOperation {
  public:

   //destructor
   
   virtual ~TerritoryOperation() {}
   
   /**
    * If the operation is a selection operation, membership will be
    * indicated by the return value. Otherwise, the return value is
    * undefined.
    *
    * \param t -- The Territory to operate on.
    */
   virtual bool operator()(Territory * t) =0; 
   
};

#endif
