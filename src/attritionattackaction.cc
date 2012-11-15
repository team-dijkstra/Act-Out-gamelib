#include "attritionattackaction.h"
#include "filterbyunittype.h"
#include "landterritory.h"
#include "traditionalarmy.h"
#include "defaultphase.h"

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
   Territory::unitContainer defendUnits = T->units(new FilterByUnitType(this->parent));
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
   
