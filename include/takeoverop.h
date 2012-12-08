/*
Act-Out! game library - implements generic game logic.
Copyright (C) 2012 Rio Lowry, Chris Pinter, Matt Voroney

This file is part of Act-Out!

Act-Out! is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Act-Out! is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Act-Out!.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * \file takeoverop.h
 */

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

   /// sets the owner of t to conquerer
   /// \param t -- the Territory whose owner is set to the conquerer
   /// \return always false
   bool operator()(Territory * t) {
      t->owner(conquerer);

      return false;
   }

  private:
   Player * conquerer; ///< the Player that is the conquerer
};

#endif /* TAKEOVER_H */

