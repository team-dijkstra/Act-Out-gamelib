
#ifndef FAKE_PLAYER_H
#define FAKE_PLAYER_H

#include "player.h"

/// FakePlayer class for testing
///
/// \tparam T this is just a dummy param so that this class will be
//      treated as a template class.
template<typename T = int>
class FakePlayer : public Player {
  public:
   
   FakePlayer(const char * nm) : pName(nm) {}
   bool alive() const {
      return true;
   }
   std::string name() const {
      return pName;
   }
   phaselist remainingPhases() const {
      return phaselist();
   }
   Unit::actionContainer actions(TerritoryOperation * op) const {
      return Unit::actionContainer();
   }
   void nextPhase() {}

  private:
   std::string pName;
};

#endif /* FAKE_PLAYER_H */

