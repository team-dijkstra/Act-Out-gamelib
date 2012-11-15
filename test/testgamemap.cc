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
/*
 * cpsc 2720 - Project - GameMap Test cases
 */

#include <iterator>
#include <utility>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "gamemap.h"
#include "testgamemap.h"
#include "fk_faketerritory.h"

void TestGameMap::setUp() {
   GameMap::AdjacencyList tal;
   const int nterritories = 9;
   const char * territories[] = {
      "spain", "italy", "brazil", "narnia",
      "gotham city", "metropolis", "alexandria", 
      "danger island", "danger island"
   };

   for (int i = 0; i < nterritories; i++) {
      existing_territories.push_back(territories[i]);
   }

   std::back_insert_iterator<GameMap::AdjacencyList> it(tal);
   for (int i = 0; i + 1 < nterritories; i++) {
      *it = std::make_pair(
         new FakeTerritory(territories[i]), 
         new FakeTerritory(territories[i + 1])
      ); 
   }

   game_map = createGameMap(tal);
}

void TestGameMap::tearDown() {
   existing_territories.clear();
   delete game_map;
}

GameMap* TestGameMap::createGameMap(const GameMap::AdjacencyList & tal) {
    /// \todo throw an appropriate exception?
    return NULL;
}

/// \test ensure that find works for non-existent elements.
void TestGameMap::find_returns_marker_token_for_non_existent_items() {
   Territory* temp = game_map->find("foobar");
   CPPUNIT_ASSERT(GameMap::end() == temp);
}

/// \test ensure that find works for existent elements.
void TestGameMap::find_returns_position_for_existent_items() {
   for (
      namelist::const_iterator it = existing_territories.begin(); 
      it != existing_territories.end(); 
      it++
   ) {
      Territory * result = game_map->find(*it);
      // make sure the position is valid.
      CPPUNIT_ASSERT(GameMap::end() != result);
      // make sure the right territory is returned.
      CPPUNIT_ASSERT(result->name() == *it);
   }
}

/// \test ensure that non-existent items do not have any adjacencies.
void TestGameMap::adjacencies_returns_empty_list_for_non_existent_items() {
   FakeTerritory ft("foobar");
   GameMap::TerritoryList tl;
   tl = game_map->adjacencies(&ft);

   CPPUNIT_ASSERT(tl.empty());
}

/// \test ensure that existent but non connected items do not have 
///       adjacencies.
void TestGameMap::adjacencies_returns_empty_list_for_existent_item_with_no_connections() {
   Territory * t = game_map->find("danger island");
   GameMap::TerritoryList tl;
   tl = game_map->adjacencies(t);

   CPPUNIT_ASSERT(tl.empty());
}

/// \test ensure that all adjacent items are returned, and that no 
///       non-adjacent items are returned.
void TestGameMap::adjacencies_returns_all_and_only_adjacent_items() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that the traversal part of the traverse operation works.
void TestGameMap::traverse_visits_all_territories() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that the visitor part of the traverse operation works.
void TestGameMap::traverse_applies_operation_transformations() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that filter works for selected sets of size 0.
void TestGameMap::filter_returns_empty_list_if_filter_selects_no_elements() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that filter works for selections that include everything.
void TestGameMap::filter_returns_all_elements_if_filter_selects_all_elements() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that filter works for non-empty proper subset selections.
void TestGameMap::filter_returns_all_and_only_selected_elements() {
   CPPUNIT_FAIL("Test not implemented.");
}

