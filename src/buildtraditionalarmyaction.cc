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
/** \file buildtraditionalarmyaction.cc
 * Implementation file for BuildTraditionalArmyAction class
 * Detatailed descriptions of each method are in the header file
 */
#include "buildtraditionalarmyaction.h"
#include "phase.h"
#include "territory.h"
#include "traditionalarmy.h"
#include "config.h"

const std::string BuildTraditionalArmyAction::NAME = "BuildTraditionalArmy";

/// \deprecated This constructor is kept to maintain compatibility with old tests.
BuildTraditionalArmyAction::BuildTraditionalArmyAction(Phase*, Unit * par): DefaultAction(par)
{}

BuildTraditionalArmyAction::BuildTraditionalArmyAction(Unit * par): DefaultAction(par)
{}

std::string BuildTraditionalArmyAction::name() const
{
   return NAME;
}

bool BuildTraditionalArmyAction::applicable(Phase* p) const
{
   return (p->name() == phase::MARSHAL);
}

void BuildTraditionalArmyAction::doaction(int nUnits, Territory* T)
{
   Unit* newArmy;
   newArmy = new TraditionalArmy(T, nUnits);
   T->addUnit(newArmy);
}

