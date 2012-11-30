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
/** \file attritionattackaction.cc
 * Implementation file for AttritionAttackAction class
 * Detatailed descriptions of each method are in the header file
 */

#include "attritionattackaction.h"
#include "filterbyunittype.h"
#include "landterritory.h"
#include "traditionalarmy.h"
#include "defaultphase.h"

using namespace game;

AttritionAttackAction::AttritionAttackAction(Unit * p): parent(p)
{
   aPhase = new DefaultPhase(std::string("Attack"));
}

AttritionAttackAction::AttritionAttackAction(Unit * p, Phase * ph): parent(p), aPhase(ph)
{}

AttritionAttackAction::~AttritionAttackAction()
{
   delete aPhase;
}

std::string AttritionAttackAction::name() const
{
   return "AttritionAttack";
}

bool AttritionAttackAction::applicable(Phase* p) const
{
   return (p->name() == aPhase->name());
}

const Unit * AttritionAttackAction::unit() const
{
   return parent;
}

const Territory * AttritionAttackAction::source() const
{
   return parent->whereAt();
}
void AttritionAttackAction::doaction(int nUnits, Territory * T)
{
   std::string attackUnitName = parent->name();
   Player * attacker = parent->whereAt()->owner();
   Player * defender = T->owner();
   if(attacker == defender)
      return;
   int attackUnits = parent->numUnits();
   if(nUnits > attackUnits)
      nUnits = attackUnits;
   FilterByUnitType fut(this->parent);
   Territory::unitContainer defendUnits = T->units(&fut);
   Territory::unitContainer::iterator it;
   it = defendUnits.find(attackUnitName);
   if(it != defendUnits.end())
   {
      int attrition = 0;
      int defendnUnits = it->second->numUnits();
      if(defendnUnits < nUnits)
	 //more attackers than defenders
	 attrition = defendnUnits;
      else
	 //less/equal attackers than defenders
	 attrition = nUnits;
      int defendUnitsLeft = it->second->decrease(attrition);
      parent->decrease(attrition);
      int attackUnitsLeft = nUnits - attrition;
      if(defendUnitsLeft == 0 && attackUnitsLeft > 0)
      {
	 T->owner(attacker);
	 it->second->increase(attackUnitsLeft);
	 parent->decrease(attackUnitsLeft);
      }
   }
   else
   {
      T->owner(attacker);
      T->addUnit(new TraditionalArmy(T, nUnits));
      parent->decrease(nUnits);
   }
}
   
