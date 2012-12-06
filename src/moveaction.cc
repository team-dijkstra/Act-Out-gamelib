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
//#include "buildtraditionalarmyaction.h"
//#include "filterbyunittype.h"
//#include "landterritory.h"
//#include "traditionalarmy.h"

#include "territory.h"
#include "player.h"
#include "unit.h"
#include "phase.h"
#include "config.h"

const std::string MoveAction::NAME = "Move";

/// \deprecated This constructor is kept to maintain compatibility with old tests.
MoveAction::MoveAction(Phase *, Unit * par): DefaultAction(par)
{}

MoveAction::MoveAction(Unit * par): DefaultAction(par)
{}

std::string MoveAction::name() const
{
   return NAME;
}

bool MoveAction::applicable(Phase* p) const
{
   return (p->name() == phase::REDEPLOY);
}

void MoveAction::doaction(int nUnits, Territory * T)
{
   // not in a valid state to perform the action. 
   if (Action::State::READY != state() && Action::State::PENDING != state()) return;
   
   const Player * us = unit()->whereAt()->owner();
   const Player * them = T->owner();
   
   if(us != them) {
      /// \todo set status message?
      setState(Action::State::INVALID);
      return;
   }

   Unit * moving;
   moving = this->m_parent->split(nUnits);
   T->addUnit(moving);

   setState(Action::State::SUCCEEDED);
}
   
