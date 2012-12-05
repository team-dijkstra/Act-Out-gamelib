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
/** \file 
 * Contains tests for the  class
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "landterritory.h"
#include "defaultplayer.h"
#include "filterbyallunittypes.h"
#include "builderunit.h"
#include "traditionalarmy.h"
#include "altgamemap.h"
#include <map>
#include <algorithm>
#include <vector>


/// Class containing the test cases for LandTerritory. The LandTerritory
/// is exercised through its interface Territory.
class TestAltGameMap  : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestAltGameMap);
   CPPUNIT_TEST(altgamemap_adjacencies_should_return_all_adjacent_territories_of_passed_territory);
   CPPUNIT_TEST(altgamemap_players_should_return_all_territories_owned_by_passed_player);
   //CPPUNIT_TEST(altgamemap_filter_should_List_all_territories_that_match_passed_territoryoperation);

   //CPPUNIT_TEST();
   //CPPUNIT_TEST();
   CPPUNIT_TEST_SUITE_END();
   
private:
   GameMap * g;
   Territory *t1, *t2, *t3 , *t4;
   GameMap::TerritoryList al1, al2, al3, al4;
   AltGameMap::m_adjList mymap;
   Player *p1, *p2;
   
public:
   /// \cond SETUPTEARDOWNTERRITORYTEST
   // initialization for the test territory
   void setUp() {
      p1 = new DefaultPlayer(std::string("Farnsworth"));
      p2 = new DefaultPlayer(std::string("Kif"));
      //create territories
      t1 = new LandTerritory(std::string("Fry"),p1);
      t2 = new LandTerritory(std::string("Leela"),p2);
      t3 = new LandTerritory(std::string("Bender"),p1);
      t4 = new LandTerritory(std::string("Hermes"),p1);
      // setup territory lists
      al1.push_back(t2);al1.push_back(t3);
      al2.push_back(t1);al2.push_back(t3);al2.push_back(t4);
      al3.push_back(t1);al3.push_back(t2);al3.push_back(t4);
      al4.push_back(t2);al4.push_back(t3);
      // create adjacency list
      mymap[t1] = al1;
      mymap[t2] = al2;
      mymap[t3] = al3;
      mymap[t4] = al4;
      
      g = new AltGameMap(mymap);

   }
   // frees memory for the territorys
   void tearDown() {
      //delete t1;
      //delete t2;
      //delete t3;
      //delete t4;
      delete g;
      delete p1;
      delete p2;  
   }
   /// \endcond
   
   
   /// \test ensure that adjacencies() returns all and only adjacent territories
   void altgamemap_adjacencies_should_return_all_adjacent_territories_of_passed_territory()  {
      GameMap::TerritoryList got;
      got = g->adjacencies(t1);
      CPPUNIT_ASSERT(got == al1);

      got = g->adjacencies(t2);
      CPPUNIT_ASSERT(got == al2);
      
      got = g->adjacencies(t3);
      CPPUNIT_ASSERT(got == al3);

      got = g->adjacencies(t4);
      CPPUNIT_ASSERT(got == al4

	 );
   }

   /// \test ensure that all and only player's territories are returned
   void altgamemap_players_should_return_all_territories_owned_by_passed_player()  {
      
      GameMap::TerritoryList got, check;
      GameMap::TerritoryList::iterator git;

      got = g->players(p1);
      
      check.push_back(t1);
      check.push_back(t3);
      check.push_back(t4);

      CPPUNIT_ASSERT(check.size() == got.size());

      git = find(got.begin(), got.end(), t1);
      CPPUNIT_ASSERT(git != got.end());

      git = find(got.begin(), got.end(), t2);
      CPPUNIT_ASSERT(git == got.end());

      git = find(got.begin(), got.end(), t3);      
      CPPUNIT_ASSERT(git != got.end());

      git = find(got.begin(), got.end(), t4);
      CPPUNIT_ASSERT(git != got.end());
      
      
   }
   
   /// \test ensure filter works
   void altgamemap_filter_should_return_filteredlist()  {
      
      GameMap::TerritoryList got, check;
      GameMap::TerritoryList::iterator git;

      got = g->players(p1);
      
      check.push_back(t1);
      check.push_back(t3);
      check.push_back(t4);

      CPPUNIT_ASSERT(check.size() == got.size());

      git = find(got.begin(), got.end(), t1);
      CPPUNIT_ASSERT(git != got.end());

      git = find(got.begin(), got.end(), t2);
      CPPUNIT_ASSERT(git == got.end());

      git = find(got.begin(), got.end(), t3);      
      CPPUNIT_ASSERT(git != got.end());

      git = find(got.begin(), got.end(), t4);
      CPPUNIT_ASSERT(git != got.end());
      
      
   }
   // \test ensure 
   //void altgamemap_filter_should_List_all_territories_that_match_passed_territoryoperation()  {

      // CPPUNIT_ASSERT(territoryA->owner() == ply2);
   //}

   // \test ensure a 
   //void altgamemap_unit_should_()  {
   
      // CPPUNIT_ASSERT(a.size() != 0);

   //}

   // \test ensure  
   //void altgamemap_should_not_(){

      // CPPUNIT_ASSERT(it->second->numUnits() == 2);
   //}
   
};

/// \cond TestTerritoryREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestAltGameMap);
/// \endcond
