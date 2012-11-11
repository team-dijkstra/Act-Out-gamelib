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
#ifndef TERRITORY_H
#define TERRITORY_H

#include <string>
#include <vector>
#include <map>

class Player;
class Filter;
class Unit;

/// An interface class to represent a Territory 
class Territory {
  public:

   typedef std::map<std::string, Unit*> unitContainer;
   
   virtual ~Territory() {}

   //accessors
   /// \return the Player object that currently owns this Territory
   virtual Player* owner() const =0;
   
   /// \return a string, the name of the Territory
   virtual std::string name() const =0;

   /// \param[in] 
   /// \return a vector of Units that are on this Territory 
   virtual unitContainer units(Filter* f) const =0;

   //mutators
   /// \param[in] reference to Player object 
   /// \post sets Territory owner to the passed Player object
   virtual void owner(Player*) =0;
   virtual void addUnit(Unit*) =0;
};

#endif
