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

#include <vector>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "gamemap.h"

/// GameMap test suite.
class TestGameMap : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestGameMap);
   CPPUNIT_TEST(find_returns_marker_token_for_non_existent_items);
   CPPUNIT_TEST(find_returns_position_for_existent_items);
   CPPUNIT_TEST(adjacencies_returns_empty_list_for_non_existent_items);
   CPPUNIT_TEST(adjacencies_returns_empty_list_for_existent_item_with_no_connections);
   CPPUNIT_TEST(adjacencies_returns_all_and_only_adjacent_items);
   CPPUNIT_TEST(traverse_visits_all_territories);
   CPPUNIT_TEST(traverse_applies_operation_transformations);
   CPPUNIT_TEST(filter_returns_empty_list_if_filter_selects_no_elements);
   CPPUNIT_TEST(filter_returns_all_elements_if_filter_selects_all_elements);
   CPPUNIT_TEST(filter_returns_all_and_only_selected_elements);
   CPPUNIT_TEST_SUITE_END();
  private:
   typedef std::vector<const char *> namelist;
   namelist existing_territories;
   GameMap * game_map;

   static const int nterritories = 9;
   static const char * territories[nterritories];

  public:

   // Let doxygen skip ininteresting methods.
   /// \cond
   void setUp();
   void tearDown();
   /// \endcond

   /// \brief factory method for creating GameMap objects. must be overridden
   ///        for each concrete type.
   virtual GameMap* createGameMap(
      const GameMap::AdjacencyList & tal
   );

   /// \test ensure that find works for non-existent elements.
   void find_returns_marker_token_for_non_existent_items();

   /// \test ensure that find works for existent elements.
   void find_returns_position_for_existent_items();
   
   /// \test ensure that non-existent items do not have any adjacencies.
   void adjacencies_returns_empty_list_for_non_existent_items();

   /// \test ensure that existent but non connected items do not have 
   ///       adjacencies.
   void adjacencies_returns_empty_list_for_existent_item_with_no_connections();

   /// \test ensure that all adjacent items are returned, and that no 
   ///       non-adjacent items are returned.
   void adjacencies_returns_all_and_only_adjacent_items();

   /// \test ensure that the traversal part of the traverse operation works.
   void traverse_visits_all_territories(); 

   /// \test ensure that the visitor part of the traverse operation works.
   void traverse_applies_operation_transformations(); 

   /// \test ensure that filter works for selected sets of size 0.
   void filter_returns_empty_list_if_filter_selects_no_elements(); 

   /// \test ensure that filter works for selections that include everything.
   void filter_returns_all_elements_if_filter_selects_all_elements(); 

   /// \test ensure that filter works for non-empty proper subset selections.
   void filter_returns_all_and_only_selected_elements(); 

};

