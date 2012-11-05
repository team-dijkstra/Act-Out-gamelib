#ifndef CONCRETE_PLAYER_H
#define CONCRETE_PLAYER_H

#include "player.h"
#include "phase.h"
#include "action.h"
#include "operation.h"
#include "game.h"

class ConcretePlayer {
  public:
   ConcretePlayer(std::string nm, Game * g);
   ~ConcretePlayer() {}
    //accessors
   /// \return true if the player is alive (i.e. still in the
   ///         game, false otherwise
   virtual bool alive() const;

   /// \return the name of the player
   virtual std::string name() const;

   /// \return the remaining phases in this players current turn
   virtual std::vector<Phase*> remainingPhases() const;

   /// \return the valid actions that this player can perform given
   ///         this filter.
   virtual std::vector<Action*> validActions(Operation * op) const;

   //Mutator
   /// \post moves to the next phase, it the last phase is reached
   ///       reset to the first phase
   virtual void nextPhase();

  private:

   typedef std::vector<Phase*> phaselist;
   std::string name;
   bool alive;
   phaselist phases;
   phaselist::const_iterator currentPhase;
   
};

#endif
