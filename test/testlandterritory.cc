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
 * cpsc 2720 - Project - Territory Test cases
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "landterritory.h"
#include "concreteplayer.h"
#include "filterbyallunittypes.h"
#include "builderunit.h"
#include "traditionalarmy.h"
#include <map>


/// Class containing the test cases for LandTerritory. The LandTerritory
/// is exercised through its interface Territory.
class TestTerritory : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestTerritory);
   CPPUNIT_TEST(territoryname_should_be_as_constructed);
   CPPUNIT_TEST(territoryowner_should_be_as_constructed);
   CPPUNIT_TEST(territory_owner_should_be_changed_by_mutator);
   CPPUNIT_TEST(territory_unit_should_return_a_vector);
   CPPUNIT_TEST(territory_should_not_add_new_unit_of_existing_unit_type);
   CPPUNIT_TEST_SUITE_END();
   
private:
   // different territorys used in testing
   Territory * territoryA;
   Territory * territoryB;
   Player * ply1;
   Player * ply2;
   
public:
   // initialization for the test territory
   void setUp() {
      ply1 = new ConcretePlayer(std::string("player1"));
      ply2 = new ConcretePlayer(std::string("player2"));
      territoryA = new LandTerritory(std::string("Spain"), ply1);
      territoryB = new LandTerritory(std::string("Canada"), ply2);
   }

   // frees memory for the territorys
   void tearDown() {
      delete territoryA;
      delete territoryB;
      delete ply1;
      delete ply2;
   }

   /// \test ensure that the territory names are correctly reported
   void territoryname_should_be_as_constructed()  {
      std::string a="Spain", b="Canada";
      CPPUNIT_ASSERT(territoryA->name() == a);
      CPPUNIT_ASSERT(territoryB->name() == b);
   }

   /// \test ensure that the territory players are correct
   void territoryowner_should_be_as_constructed()  {
      CPPUNIT_ASSERT(territoryA->owner() == ply1);
      CPPUNIT_ASSERT(territoryB->owner() == ply2);
   }

   void territory_owner_should_be_changed_by_mutator()  {
      territoryA->owner(ply2);
      CPPUNIT_ASSERT(territoryA->owner() == ply2);
   }

   /// \todo add test for different types of units in units() function
   void territory_unit_should_return_a_vector()  {
      
      Territory::unitContainer a;
      Unit * u = new BuilderUnit(territoryA,1);
	 
      Filter * fi = new FilterByAllUnitTypes(u) ;
      a = territoryA->units(fi);
      //   territoryA->owner(ply2);
      CPPUNIT_ASSERT(a.size() != 0);
   }

   void territory_should_not_add_new_unit_of_existing_unit_type(){
      Territory::unitContainer a;
      Unit * u = new BuilderUnit(territoryA,1);
      Unit * u2 = new BuilderUnit(territoryA,1);
      Filter * fi = new FilterByAllUnitTypes(u) ;
      territoryA->addUnit(u2);
      a = territoryA->units(fi);
      Territory::unitContainer::iterator it;
      it = a.find("BuilderUnit");
      CPPUNIT_ASSERT(a.size() != 2);
      CPPUNIT_ASSERT(it->second->numUnits() == 2);
      
   }
   
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTerritory);

