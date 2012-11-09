#ifndef CONCRETE_PLAYER_H
#define CONCRETE_PLAYER_H

#include "player.h"

class Phase;
class Action;
class TerritoryOperation;
class Game;

class ConcretePlayer : public Player {
  public:
//   ConcretePlayer(std::string nm, Game * g);
   ConcretePlayer(std::string nm);
   ~ConcretePlayer() {}
   //accessors
   /// \return true if the player is alive (i.e. still in the
   ///         game, false otherwise
   bool alive() const;

   /// \return the name of the player
   std::string name() const;

   /// \return the remaining phases in this players current turn
   std::vector<Phase*> remainingPhases() const;

   /// \return the valid actions that this player can perform given
   ///         this filter.
   std::vector<Action*> validActions(TerritoryOperation * op) const;

   //Mutator
   /// \post moves to the next phase, it the last phase is reached
   ///       reset to the first phase
   void nextPhase();

  private:

   typedef std::vector<Phase*> phaselist;
   std::string pName;
   bool isAlive;
   phaselist phases;
   phaselist::const_iterator currentPhase;
   
};

#endif
