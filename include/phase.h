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
/// \brief phase.h contains the interface class Phase -- phase.h
//
/// Phase class, a simple interface class to track the different game phases

#ifndef PHASE_H
#define PHASE_H

#include <string>

/// An interface class to represent the different game phases
class Phase{
  public:

   //destructor
   
   virtual ~Phase() {}

   //accessors
   
   /// \return name of Phase
   virtual std::string name() const =0;
};

#endif
