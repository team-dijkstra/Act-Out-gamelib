/**
 * \file testnamecomparators.cc
 * Contains instantiations of test suites for name comparisons on all objects
 * that have a 'name()' attribute.
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "testnamecomparators.h"
#include "territory.h"
#include "unit.h"
#include "player.h"
#include "phase.h"
#include "util/fk_faketerritory.h"
#include "defaultplayer.h"
#include "util/fk_fakeunit.h"
#include "defaultphase.h"

/// Test suite for Territory::name() comparisons.
class TestTerritoryNameComparators : public TestNameComparators<Territory> {
   CPPUNIT_TEST_SUB_SUITE(TestTerritoryNameComparators, TestNameComparators<Territory>);
   CPPUNIT_TEST_SUITE_END();
  public:
   Territory * createObject(const char * name) {
      return new FakeTerritory(std::string(name));
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTerritoryNameComparators);

/// Test suite for Player::name() comparisons.
class TestPlayerNameComparators : public TestNameComparators<Player> {
   CPPUNIT_TEST_SUB_SUITE(TestPlayerNameComparators, TestNameComparators<Player>);
   CPPUNIT_TEST_SUITE_END();
  public:
   Player * createObject(const char * name) {
      return new DefaultPlayer(std::string(name));
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestPlayerNameComparators);

/// Test suite for Unit::name() comparisons.
class TestUnitNameComparators : public TestNameComparators<Unit> {
   CPPUNIT_TEST_SUB_SUITE(TestUnitNameComparators, TestNameComparators<Unit>);
   CPPUNIT_TEST_SUITE_END();
  public:
   Unit * createObject(const char * name) {
      return new FakeUnit(0, NULL, std::string(name));
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestUnitNameComparators);

/// Test suite for Phase::name() comparisons.
class TestPhaseNameComparators : public TestNameComparators<Phase> {
   CPPUNIT_TEST_SUB_SUITE(TestPhaseNameComparators, TestNameComparators<Phase>);
   CPPUNIT_TEST_SUITE_END();
  public:
   Phase * createObject(const char * name) {
      return new DefaultPhase(std::string(name));
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestPhaseNameComparators);
