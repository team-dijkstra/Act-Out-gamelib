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
#include "phase.h"
#include "config.h"

const std::string AttritionAttackAction::NAME = "AttritionAttack";

AttritionAttackAction::AttritionAttackAction(Unit * p): DefaultAction(p)
{}

/// \deprecated This constructor is kept to maintain compatibility with old tests.
AttritionAttackAction::AttritionAttackAction(Unit * p, Phase *): DefaultAction(p)
{}

std::string AttritionAttackAction::name() const
{
   return NAME;
}

bool AttritionAttackAction::applicable(Phase* p) const
{
   return (p->name() == phase::ATTACK);
}

void AttritionAttackAction::doaction(int nUnits, Territory * T)
{
   std::string attackUnitName = unit()->name();
   Player * attacker = unit()->whereAt()->owner();
   Player * defender = T->owner();
   
   if(attacker == defender)
      return;

   int attackUnits = unit()->numUnits();
   if(nUnits > attackUnits)
      nUnits = attackUnits;

   FilterByUnitType fut(this->m_parent);
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
      this->m_parent->decrease(attrition);
      int attackUnitsLeft = nUnits - attrition;
      if(defendUnitsLeft == 0 && attackUnitsLeft > 0)
      {
	     T->owner(attacker);
	     it->second->increase(attackUnitsLeft);
	     this->m_parent->decrease(attackUnitsLeft);
      }
   }
   else
   {
      T->owner(attacker);
      T->addUnit(new TraditionalArmy(T, nUnits));
      this->m_parent->decrease(nUnits);
   }
}
   
