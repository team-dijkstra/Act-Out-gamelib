#ifnedef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Phase;
class Action;
class Filter;

class Player {
  public:
   //accessors
   virtual bool alive() const =0;
   virtual std::string name() const =0;
   virtual std::vector<Phase> remainingPhases() const =0;
   virtual std::vector<Action> validActions(Filter * f) const =0;

   //Mutator
   virtual void nextPhase() =0;
   virtual ~Player() {}
};

#endif
