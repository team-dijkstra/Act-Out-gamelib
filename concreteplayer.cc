#include "concreteplayer.h"

ConcretePlayer::ConcretePlayer(std::string nm):pName(nm),isAlive(true)
{}

bool ConcretePlayer::alive() const{
   return isAlive;
}

/// \return the name of the player
std::string ConcretePlayer::name() const{
   return pName;
}

/// \return the remaining phases in this players current turn
std::vector<Phase*> ConcretePlayer::remainingPhases() const{}

/// \return the valid actions that this player can perform given
///         this filter.
std::vector<Action*> ConcretePlayer::validActions(Operation * op) const{}

//Mutator
/// \post moves to the next phase, it the last phase is reached
///       reset to the first phase
void ConcretePlayer::nextPhase(){}
