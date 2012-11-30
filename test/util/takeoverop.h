
#ifndef TAKEOVER_H
#define TAKEOVER_H

#include <string>
#include "territoryoperation.h"

namespace game {
   class Player;
}

/// An operation that sets each territory owner to the conquering Player
///
template<typename T = int>
class TakeOver : public TerritoryOperation {
  public:
   TakeOver(game::Player * c) : conquerer(c) {}

   bool operator()(game::Territory * t) {
      t->owner(conquerer);

      return false;
   }

  private:
   game::Player * conquerer;
};

#endif /* TAKEOVER_H */

