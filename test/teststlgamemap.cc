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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "stlgamemap.h"
#include "testgamemap.h"

/// StlGameMap test suite.
class TestStlGameMap : public TestGameMap {
   CPPUNIT_TEST_SUB_SUITE(TestStlGameMap, TestGameMap);
   CPPUNIT_TEST_SUITE_END();
  private:
   StlGameMap * game_map;
  public:

   // let doxygen skip unintresting methods.
   /// \cond
   void setUp() {
      TerritoryList tl;
      TerritoryConnections tc;
      game_map = new StlGameMap(tl, tc);
      init(game_map);
   }

   void tearDown() {
      delete game_map;
   }
   /// \endcond

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestStlGameMap);

