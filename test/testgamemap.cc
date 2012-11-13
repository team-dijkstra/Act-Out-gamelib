/*
 * cpsc 2720 - Project - GameMap Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "gamemap.h"
#include "testgamemap.h"

void TestGameMap::init(GameMap * gm) {
   game_map = gm;
}

/// \test ensure that find works for non-existent elements.
void TestGameMap::find_returns_marker_token_for_non_existent_items() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that find works for existent elements.
void TestGameMap::find_returns_position_for_existent_items() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that non-existent items do not have any adjacencies.
void TestGameMap::adjacencies_returns_empty_list_for_non_existent_items() {
   CPPUNIT_FAIL("Test not implemented.");
}

/// \test ensure that existent but non connected items do not have 
///       adjacencies.
void TestGameMap::adjacencies_returns_empty_list_for_existent_item_with_no_connections() {
   CPPUNIT_FAIL("Test not implemented.");
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

