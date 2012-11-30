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

#ifndef FAKE_PLAYER_H
#define FAKE_PLAYER_H

#include "player.h"

/// FakePlayer class for testing
///
/// \tparam T this is just a dummy param so that this class will be
//      treated as a template class.
template<typename T = int>
class FakePlayer : public game::Player {
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
   game::Unit::actionContainer actions(TerritoryOperation *) const {
      return game::Unit::actionContainer();
   }
   bool nextPhase() {
      return false;    
   }

  private:
   std::string pName;
};

#endif /* FAKE_PLAYER_H */

