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
/** \file moveaction.cc
 * Implementation file for MoveAction class
 * Detatailed descriptions of each method are in the header file
 */
#include "moveaction.h"
#include "buildtraditionalarmyaction.h"
#include "filterbyunittype.h"
#include "landterritory.h"
#include "traditionalarmy.h"

MoveAction::MoveAction(Phase * p, Unit * par): aPhase(p), parent(par)
{}

std::string MoveAction::name() const
{
   return "Move";
}

bool MoveAction::applicable(Phase* p) const
{
   return (p->name() == aPhase->name());
}

const Unit * MoveAction::unit() const
{
   return parent;
}

const Territory * MoveAction::source() const
{
   return parent->whereAt();
}

void MoveAction::doaction(int nUnits, Territory * T)
{
   Player * here, * there;
   here = parent->whereAt()->owner();
   there = T->owner();
   if(here != there)
      return;
   Unit * moving;
   moving = parent->split(nUnits);
   T->addUnit(moving);
}
   
