#include "moveaction.h"

std::string MoveAction::name() const
{
   return "MoveAction";
}

bool MoveAction::applicable(Phase* p) const
{
   return (p->name() == "Redeploy");
}

void MoveAction::doaction(int nUnits, Territory * T)
{
   /// \todo do stuff here
}
   
