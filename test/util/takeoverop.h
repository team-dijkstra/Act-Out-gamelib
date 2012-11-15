
#ifndef TAKEOVER_H
#define TAKEOVER_H

#include <string>
#include "territoryoperation.h"

class Player;

/// An operation that sets each territory owner to the conquering Player
///
template<typename T = int>
class TakeOver : public TerritoryOperation {
  public:
   TakeOver(Player * c) : conquerer(c) {}

   bool operator()(Territory * t) {
      t->owner(conquerer);
   }

  private:
   Player * conquerer;
};

#endif /* TAKEOVER_H */

