/// \file
/// \brief Interface file for Player class -- player.h
//
/// Player Interface Class

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Phase;
class Action;
class Filter;

/// Player Interface Class specified the Player Behaviours
class Player {
  public:
   //accessors
   /// \return true if the player is alive (i.e. still in the
   ///         game, false otherwise
   virtual bool alive() const =0;

   /// \return the name of the player
   virtual std::string name() const =0;

   /// \return the remaining phases in this players current turn
   virtual std::vector<Phase> remainingPhases() const =0;

   /// \return the valid actions that this player can perform given
   ///         this filter.
   virtual std::vector<Action> validActions(Filter * f) const =0;
   //perhaps this should be:
   //virtual std::vector<Action> validActions(Phase * p) const =0; //?

   //Mutator
   /// \post moves to the next phase, it the last phase is reached
   ///       reset to the first phase
   virtual void nextPhase() =0;
   
   virtual ~Player() {}
};

#endif
