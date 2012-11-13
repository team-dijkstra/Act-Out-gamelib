
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

