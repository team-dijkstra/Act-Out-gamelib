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
   
