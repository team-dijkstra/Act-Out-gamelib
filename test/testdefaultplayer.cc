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
/** \file testdefaultplayer.cc
 * Contains tests for the DefaultPlayer class
 */
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <algorithm>
#include "defaultplayer.h"
#include "defaultphase.h"
#include "altgamemap.h"
#include "landterritory.h"
#include "traditionalarmy.h"
#include "attritionattackaction.h"
#include "buildtraditionalarmyaction.h"
#include "moveaction.h"
#include "filterbyterritoryowner.h"



/// Class containing the test cases for DefaultPlayer. The DefaultPlayer
/// is exercised through its interface Player.
class TestPlayer : public CppUnit::TestFixture {
   CPPUNIT_TEST_SUITE(TestPlayer);
   CPPUNIT_TEST(player_name_should_be_as_constructed);
   CPPUNIT_TEST(player_should_be_alive_when_constructed);
   CPPUNIT_TEST(player_alive_should_be_false_when_player_owns_no_territories);
   CPPUNIT_TEST(player_remainingPhases_should_return_a_phaselist);
   CPPUNIT_TEST(player_nextPhases_should_move_to_next_element_in_phaselist);
   CPPUNIT_TEST(player_actions_should_return_action_container_of_applicable_actions_for_phase);
   
   CPPUNIT_TEST_SUITE_END();
   
  private:
   /// \cond SETUPTEARDOWNPLAYERTEST
   // different players used in testing
   Player * playerA;
   Player * playerB;
   Player::phaselist Plist;
   Player::phaselist::iterator it;
  public:
   // initialization for the test player
   void setUp() {
      Plist.push_back(new DefaultPhase("Marshall"));
      Plist.push_back(new DefaultPhase("Attack"));
     
      playerA = new DefaultPlayer(std::string("Player1"),Plist);
      playerB = new DefaultPlayer(std::string("Player2"),Plist);
   }
   // frees memory for the players
   void tearDown() {
      delete playerA;
      delete playerB;
      for (it=Plist.begin();it!=Plist.end();++it)
	 delete *it;
   }
   /// \endcond
   
   
   /// \test ensure that the player names are correctly reported
   void player_name_should_be_as_constructed()  {
      CPPUNIT_ASSERT(playerA->name() == "Player1");
      CPPUNIT_ASSERT(playerB->name() == "Player2");
   }

   void player_should_be_alive_when_constructed()
   {
      CPPUNIT_ASSERT(playerA->alive() == true);
      CPPUNIT_ASSERT(playerB->alive() == true);
   }

   void player_alive_should_be_false_when_player_owns_no_territories()
   {
      Territory * t1, *t2, * t3,* t4;
      GameMap::TerritoryList al1, al2, al3, al4;
      AltGameMap::m_adjList mymap;
      GameMap * g;
      Player *p1, *p2;

      
      //SETUP
     
      //territories
      t1 = new LandTerritory(std::string("Fry"),playerA);
      t2 = new LandTerritory(std::string("Leela"),playerA);
      t3 = new LandTerritory(std::string("Bender"),playerA);
      t4 = new LandTerritory(std::string("Hermes"),playerA);

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

      //players
      p1 = new DefaultPlayer(std::string("Farnsworth"),Plist,g);
      p2 = new DefaultPlayer(std::string("Kif"),Plist,g );

      t1->owner(p2);
      
      CPPUNIT_ASSERT(p1->alive() == false);
      CPPUNIT_ASSERT(p2->alive() == true);

      //delete t1;delete t2;delete t3; delete t4;
      delete g;
      delete p1; delete p2;
   } 

   /// \test checks that phaselist is correctly returned
   void player_remainingPhases_should_return_a_phaselist()
   {
      Player::phaselist Pl2;
      Pl2 = playerA->remainingPhases();
      CPPUNIT_ASSERT(Plist.size() == Pl2.size());
      CPPUNIT_ASSERT(Plist == Pl2);
      CPPUNIT_ASSERT(*(Plist.begin()) == *(Pl2.begin()));
      
   }

   /** \test checks that nextPhase properly sets DefaultPlayer::currentPhase
    *  to the proper next phase
    */
   void player_nextPhases_should_move_to_next_element_in_phaselist()
   {
      it = Plist.begin();
      ++it;
      Player::phaselist Pl2;
      Player::phaselist::iterator it2;
      playerA->nextPhase();
      Pl2 = playerA->remainingPhases();
      it2 = Pl2.begin();
      //CPPUNIT_ASSERT(Plist.size() == Pl2.size());
      //CPPUNIT_ASSERT(Plist == Pl2);
      CPPUNIT_ASSERT(*(it2) == *(it));
            
      playerA->nextPhase();
      Pl2 = playerA->remainingPhases();
      it2 = Pl2.begin();
      it = Plist.begin();
      CPPUNIT_ASSERT(*(it2) == *(it));
   }

   void player_actions_should_return_action_container_of_applicable_actions_for_phase()
   {
      Plist.push_back(new DefaultPhase("Redeploy"));

      /*std::cout<<"\n\n\n"
	       << Plist[0]->name() << "\n"
	       << Plist[1]->name() << "\n"
	       << Plist[2]->name()
	       <<"\n\n\n";*/
      Territory * t1, *t2, * t3,* t4;
      GameMap::TerritoryList al1, al2, al3, al4;
      AltGameMap::m_adjList mymap;
      GameMap * g;
      Player *p1, *p2;

      
      //SETUP
     
      //territories
      t1 = new LandTerritory(std::string("Fry"),playerA);
      t2 = new LandTerritory(std::string("Leela"),playerA);
      t3 = new LandTerritory(std::string("Bender"),playerA);
      t4 = new LandTerritory(std::string("Hermes"),playerA);

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

      //players
      p1 = new DefaultPlayer(std::string("Farnsworth"),Plist,g);
      p2 = new DefaultPlayer(std::string("Kif"),Plist,g );

      //setup first army
      Unit::actionContainer  act1, getActions;
      Action * a,*b,*c;
      TraditionalArmy * army;
      t1->owner(p2);
      //TraditionalArmy * army = new TraditionalArmy(t1,1,getActions);
      army = new TraditionalArmy(t1);
      t1->addUnit(army);
      //add actions to first army's action container
      a = new BuildTraditionalArmyAction(Plist[0],army);
      getActions.push_back(a);
      b = new AttritionAttackAction(army,Plist[1]);
      getActions.push_back(b);
      c = new MoveAction(Plist[2],army);
      getActions.push_back(c);
      
      army->setActions(getActions);
      /*
	check that phases are returned on first territory
      */
      TerritoryOperation * op;
      op = new FilterByTerritoryOwner(p2->name());
      act1 = p2->actions(op);
      Unit::actionContainer::iterator actIT;
      actIT = find( act1.begin(), act1.end(), a);
      //std::cout<<"\n"<<(*actIT)->name()<<"\n";
      CPPUNIT_ASSERT(actIT != act1.end() );

      actIT = find( act1.begin(), act1.end(), b);
      //std::cout<<"\n"<<(*actIT)->name()<<"\n";
      CPPUNIT_ASSERT(actIT == act1.end() );

      actIT = find( act1.begin(), act1.end(), c);
      //std::cout<<"\n"<<(*actIT)->name()<<"\n";
      CPPUNIT_ASSERT(actIT == act1.end() );
      //delete army;
      delete op;
/*
      //setup 2nd army
      t2->owner(p1);
      army = new TraditionalArmy(t2);
      t2->addUnit(army);
      //add actions to 2nd army's action container
      a = new BuildTraditionalArmyAction(Plist[0],army);
      getActions.push_back(a);
      a = new AttritionAttackAction(army,Plist[1]);
      getActions.push_back(a);
      a = new MoveAction(Plist[2],army);
      getActions.push_back(a);
      army->setActions(getActions);
/*
      //setup 3rd army
      t3->owner(p2);
      army = new TraditionalArmy(t3);
      t3->addUnit(army);
      //add actions to 3rd army's action container
      a = new BuildTraditionalArmyAction(Plist[0],army);
      getActions.push_back(a);
      a = new AttritionAttackAction(army,Plist[1]);
      getActions.push_back(a);
      a = new MoveAction(Plist[2],army);
      getActions.push_back(a);
      army->setActions(getActions);
      
      //setup 4th army
      t2->owner(p1);
      army = new TraditionalArmy(t2);
      t2->addUnit(army);
      //add actions to 2nd army's action container
      a = new BuildTraditionalArmyAction(Plist[0],army);
      getActions.push_back(a);
      a = new AttritionAttackAction(army,Plist[1]);
      getActions.push_back(a);
      a = new MoveAction(Plist[2],army);
      getActions.push_back(a);
      army->setActions(getActions);
*/
      
      

      delete g;
      delete p1; delete p2;
   }
};
/// \cond TestPlayerREGISTRATION
CPPUNIT_TEST_SUITE_REGISTRATION(TestPlayer);
/// \endcond
