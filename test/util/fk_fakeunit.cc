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
/** \file fk_fakeunit.h
 * Imlements FakeUnit Test class to implement the Unit interface
 */
#include "fk_fakeunit.h"
#include "action.h"

using namespace std;

//FakeUnit::FakeUnit(int nunit, Territory * t,  vector<Action*> uActs):nUnits(nunit), tWhere(t), uActions(uActs)
FakeUnit::FakeUnit(int nunit, Territory * t, string s):nUnits(nunit), tWhere(t), uName(s)
{
   //uName = "FakeUnit";   
}

int FakeUnit:: increase (int u)
{
   nUnits += u;
   return nUnits;
}

int FakeUnit::decrease (int u)
{
   int tdec = u;
   nUnits = (tdec > nUnits ? 0 : nUnits - tdec);
   return nUnits;
}

int FakeUnit::numUnits() const
{
   return nUnits;
}

Territory* FakeUnit::whereAt() const
{
   return tWhere;
}

std::string FakeUnit::name() const
{
   return uName;
}

std::vector<Action*> FakeUnit::actions() const
{
   return uActions;
}

