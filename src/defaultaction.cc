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
/** 
 * \file defaultaction.cc
 *
 * Default Implementation file for Action Interface
 * Detatailed descriptions of each method are in the header file
 */
#include <string>
#include "defaultaction.h"
#include "phase.h"
#include "territory.h"
#include "unit.h"

/// \todo is there a safer way of initializing this array? What if the indicies change?
const std::string DefaultAction::status_msg[Action::State::LAST] = {
    " is ready to perform",
    " is pending",
    " was performed successfully",
    " was attempted but failed",
    " is not valid in this context"
};

const std::string DefaultAction::NAME = "DefaultAction";

DefaultAction::DefaultAction(Unit * par): m_parent(par), m_state(Action::State::READY) {}

std::string DefaultAction::name() const {
   return NAME;
}

std::string DefaultAction::description() const {
    return name() + " performed by " + unit()->name() + " located in " + source()->name();
}

std::string DefaultAction::status() const {
    return name() + status_msg[m_state];
}

// cppcheck-suppress unusedFunction
Action::State DefaultAction::state() const {
    return m_state;
}

bool DefaultAction::applicable(Phase* p) const {
   // the default action is not applicable at all since it is abstract.
   return false;
}

const Unit * DefaultAction::unit() const {
   return m_parent;
}

const Territory * DefaultAction::source() const {
   return m_parent->whereAt();
}

void DefaultAction::setState(Action::State s) {
   m_state = s;
}

