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
 *  \brief A basic driver program for our game library -- driver.cc
 *
 *  Contains the main() function for implementing a basic game
 */
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <set>

#include "defaultplayer.h"
#include "landterritory.h"
#include "defaultphase.h"
//#include "stlgamemap.h"
#include "attritionattackaction.h"
#include "moveaction.h"
#include "buildtraditionalarmyaction.h"
#include "traditionalarmy.h"
#include "config.h"

using namespace std;

/// adjacency list of territories
typedef vector< pair< Territory*, Territory* > > adjList;
/// list of all players
typedef vector< Player* > playerList;
/// list of commands
typedef map< string, int > comList;
/// list of phases
typedef Player::phaselist phaseList;
/// list of territories
typedef set<Territory* > territorylist;

/** This is a temporary class implementation of functionality that is needed from the Game and DriverGameMap
 * interface classes so we could complete our driver class for demo purposes. Elemets of this will be
 * incorporated into the implementations of those clases and will be removed from the final driver program
 * other elements such as DriverGameMap::print() are more appropriate for the driver program and will remain
 */

class DriverGameMap{
public:
   /// param a -- adjList
   /// post MIL:
   ///      <br>- sets myAjL to a and inserts elements of a into allTerr
   DriverGameMap(adjList & a):myAjL(a)//, unclaimed(new DefaultPlayer(string("Unclaimed")))
   {
      adjList::iterator it;
      for(it = myAjL.begin();  it!=myAjL.end() ; ++it)
      {
	 allTerr.insert(it->first);
	 allTerr.insert(it->second);
      }
   }

   /** Convienience method for initially allocating owners to the Territories
    *  this will be handled by the implementation of the Game::SetupGame()
    */
   void setOwners(Player * p1, Player * p2)
   {
      set< Territory*>::iterator gIT;
      int m=0;
      for(gIT = allTerr.begin(); gIT != allTerr.end(); ++gIT)
      {
	 if(((m++)%2 ) == 0)
	 {
	    (*gIT)->owner(p1);
	 }
	 else
	    (*gIT)->owner(p2);
      }
   }
   /// \cond GAMEMAPOUT
   void out(){
      cout<<"";
   }
   /// 	\endcond

   /// \post prints all territories
   void print()
   {
      territorylist l = list();
      territorylist::iterator lsIT;
      for(lsIT = l.begin(); lsIT != l.end(); ++lsIT)
      {
	 cout << (*lsIT)->name() << endl;;
      }
   }

   /// \param p -- Player pointer
   /// \post prints territories of the specified Player
   void print(Player * p)
   {
      territorylist l = list(p);
      territorylist::iterator lsIT;
      for(lsIT = l.begin(); lsIT != l.end(); ++lsIT)
      {
	 cout << (*lsIT)->name() << endl;;
      }
      
   }

   /// \post returns a DriverGameMap::territorylist containing of all territories
   territorylist list()
   {
      territorylist pass;
      set< Territory*>::iterator gIT;
      for(gIT = allTerr.begin(); gIT != allTerr.end(); ++gIT)
      {
	 pass.insert(*gIT);
	 //cout << (*gIT)->name() << endl;;
      }
      return pass;
   }

   /// \param p -- Player pointer
   /// \returns DriverGameMap::territorylist containing all territories of the specified Player
   territorylist list(Player * p)
   {
      territorylist pass;
      set< Territory*>::iterator gIT;
      for(gIT = allTerr.begin(); gIT != allTerr.end(); ++gIT)
      {
	 if( (*gIT)->owner() == p)
	 {
	    pass.insert(*gIT);
	    //cout << (*gIT)->name() << endl;;
	 }
      }
      return pass;
   }

   /// \param att -- pointer to attacking territory object
   /// \param def -- pointer to defending territory object
   /// \param player -- pointer to attacking player object
   ///
   /// \returns a bool indicating true if attack sucessful, false otherwise
   bool Attack(Territory * att, Territory * def, Player * player)
   {
      
      set< Territory* >::iterator i1,i2;
      i1 = allTerr.find(att);
      i2 = allTerr.find(def);
      if(i1!=allTerr.end() && i2!=allTerr.end() )
      {
	 phaseList curr = player->remainingPhases();
	 phaseList::iterator phsIT = curr.begin();

	 Action * a = new AttritionAttackAction(new TraditionalArmy(att,10));
	 bool cando = a->applicable(*phsIT);
	 if(cando)
	 {
	    //  cout << "Can Do!\n";
	    a->doaction(1,def);
	 }

	 delete a;
	 return cando;
      }
      return false;
   }

   /// \returns a DriverGameMap::territorylist of all territories
   territorylist getSet()
   {
      return allTerr;
   }
   
private:
   adjList myAjL;
   //Player * unclaimed;
   set< Territory* > allTerr;
   
   
};

void init(map< string, int > &);
void help();
void setup(DriverGameMap *&, playerList &, phaseList&);
void showmap(DriverGameMap *&);
void myterritories(DriverGameMap *&,Player *);
void playPhase(DriverGameMap *&, playerList &, Player *&);
void nextPhase(DriverGameMap *&, playerList &, Player *&);
void attack(DriverGameMap *&, playerList &, Player *&);
bool playGame(DriverGameMap *&, playerList &, comList&, Player *&);
bool isWinner(DriverGameMap *&, playerList&, Player *);
void shutupcppcheck()
{
   Player * p1 = new DefaultPlayer("p1");
   Territory * la = new LandTerritory("la", p1);
   Unit * ta = new TraditionalArmy(la);
   Phase * ph1 = new DefaultPhase("phase");
   AttritionAttackAction aaa(ta);
   MoveAction ma(ph1, ta);
   BuildTraditionalArmyAction btaa(ph1, ta);
   aaa.unit();aaa.source();ma.unit();ma.source();btaa.unit();btaa.source();
   delete p1;
   delete la;
   delete ta;
   delete ph1;
}

/// Main driver funtion
int main()
{
   shutupcppcheck();
   map< string, int > commands;
   
   init(commands);

   DriverGameMap * myDriverGameMap;
   playerList pList;
   phaseList phsList;
   phaseList::iterator phsIT;
   
   setup(myDriverGameMap,pList,phsList);
   myDriverGameMap->setOwners(pList[0],pList[1]);
   Player * currentTurn;
   currentTurn = pList[0];
   cout << endl;
   help();
   cout << "Game is ready, "<< currentTurn->name() << " will proceed first" << endl<<endl;
   //cout << "The commands are: "<<endl;
   
   do
   {
      phaseList curr = currentTurn->remainingPhases();
      phsIT = curr.begin();
      //string cp = phsIT->name();
      string cp =  (*phsIT)->name();
      cout << "The current player is: " <<currentTurn->name();
      cout << " The current phase is: " <<cp <<endl;
   }
   while(playGame(myDriverGameMap, pList, commands, currentTurn));
   return 0;
}

/// \param[in,out] commands -- reference to a comList of commands
/// \post initializes the command list
void init(map< string, int > & commands)
{
   int index = 0;
   commands["help"] = index++;
   //commands["'help'"] = index++;
   commands["showmap"] = index++;
   commands["showme"] = index++;
   commands["play"] = index++;
   commands["next"] = index++;
   commands["attack"] = index++;
   commands["quit"] = index++;
   //commands[""] = index++;
}

/// \post outputs help screen to standard out
void help()
{
   cout << "===List Of Commands==="<<endl;
   cout << "'help': display these help instructions."<<endl;
   cout << "'showmap': display all the territories."<<endl;
   cout << "'showme': display the list of territories owned by the current player."<<endl;
   cout << "'play': Play the current player's current phase of the current turn \n\t(will automatically move on to the next phase)"<<endl;
   cout << "'next': move to the players next phase of the current turn \n\t(if no more phases are left in the current turn, this will move to the next players turn)"<<endl;
   cout << "'quit': current player quits (lame!)"<<endl;
   cout << endl;
}

/// \param gm -- pointer reference to the DriverGameMap
/// \param pL -- reference to a playerList
/// \param phsL -- reference to a phaseList
/// \post initializes the game state
void setup(DriverGameMap *& gm ,playerList& pL, phaseList& phsL)
{
   //setup phaselist
   phsL.push_back(new DefaultPhase(string(phase::MARSHAL)));
   phsL.push_back(new DefaultPhase(string(phase::ATTACK)));
   phsL.push_back(new DefaultPhase(string(phase::REDEPLOY)));
   
   string pn1,pn2;
   cout << "This game has 2 players"<<endl;
   cout << "Please enter the name of player 1: ";
   getline(cin, pn1);
   Player * p1 = new DefaultPlayer(pn1, phsL);
   cout << "Please enter the name of player 2: ";
   getline(cin, pn2);
   Player * p2 = new DefaultPlayer(pn2, phsL);
   pL.push_back(p1);
   pL.push_back(p2);
   
   // create territories
   Territory *t1 = new LandTerritory("Spain");
   Territory *t2 = new LandTerritory("Germany");
   Territory *t3 = new LandTerritory("GreatWhiteNorth");
   Territory *t4 = new LandTerritory("Sweden");
   Territory *t5 = new LandTerritory("Yankees");
   Territory *t6 = new LandTerritory("Mexico");
   
   /// create adjacency list
   adjList aL;
   aL.push_back(make_pair(t1,t2) );
   aL.push_back(make_pair(t1,t3) );
   aL.push_back(make_pair(t3,t4) );
   aL.push_back(make_pair(t2,t5) );
   aL.push_back(make_pair(t4,t5) );
   aL.push_back(make_pair(t5,t6) );

   gm = new DriverGameMap(aL);
   
}

/// \param g -- pointer reference to the DriverGameMap
/// \post prints list of all territories to standard out
void showmap(DriverGameMap *& g)
{
   //cout << "\t***Stub: All Territory List!" << endl;
   g->print();
   cout << endl;
}

/// \param g -- pointer reference to the DriverGameMap
/// \param p -- pointer to the current player
/// \post prints list of player's territories to standard out
void myterritories(DriverGameMap *& g,Player * p)
{
   //cout << "\t***Stub: "<<p->name()<<"'s Territory List!" << endl;
   g->print(p);
   cout << endl;
}

/// \param gm -- pointer reference to the DriverGameMap
/// \param pl -- reference to a playerList
/// \param player -- pointer reference to the current player
/// \post stub for enacting the players current turn
void playPhase(DriverGameMap *& gm, playerList & pl, Player *& player)
{
   phaseList curr = player->remainingPhases();
   phaseList::iterator cIT;
   cIT = curr.begin();
   string s = (*cIT)->name();
   gm->out();pl[0]->name();
   cout << "\t***Stub: Doing "<<player->name()<<"'s Current Phase: "<< s << endl;
   cout << endl;
}

/// \param gm -- pointer reference to the DriverGameMap
/// \param pl -- reference to a playerList
/// \param player -- pointer reference to the current player
/** \post moves player to next phase, if last phase in turn is reached sets next player in pl
 *  as the current player
 */
void nextPhase(DriverGameMap *& gm, playerList & pl, Player *& player)
{
   gm->out();
   bool nextPlayer = player->nextPhase();
   if(nextPlayer)
   {
      if(player->name() != pl[0]->name() )
	 player = pl[0];
      else
	 player = pl[1];
   }
   
   cout << "\t**Moving to Next Phase**" << endl;
   cout << endl;
}

/// \param g -- pointer reference to the DriverGameMap
/// \param plst -- reference to a playerList
/// \param currP -- pointer reference to the current player
/** \post asks player for attack decision and prints result to standard out
 */
void attack(DriverGameMap *& g, playerList & plst, Player *& currP)
{
   cout << "***Attack!***"<<endl;
   territorylist aL = g->getSet();
   cout << "List of All Territories:" <<endl;
   g->print();
   cout<<endl;
   cout << "Your Territories: "<<endl;
   myterritories(g, currP);
   territorylist::iterator gaLIT;
   map< string, Territory* > m;
   map< string, Territory* >::iterator mIT;
   for(gaLIT = aL.begin(); gaLIT != aL.end(); ++gaLIT)
   {
      Territory * t = (*gaLIT);
      string s = t->name();
      m[s]=t;
   }
   string s;
   cout << "Choose attacking territory: ";
   cin >> s;
   mIT = m.find(s);
   Territory * p1 = mIT->second;

   cout << "Choose defending territory: ";
   cin >> s;
   mIT = m.find(s);
   
   Territory * p2 = mIT->second;
   bool success = g->Attack(p1, p2, currP);
   cout << "\n\n *** Attack "<<(success? "Suceeded!":"Failed!")<<" ***"<<endl;

   cout << endl;
      
}


/**
 * Main UI for playing the game
 *
 * \param myGame -- pointer reference to the DriverGameMap
 * \param pList -- reference to a playerList
 * \param commands -- reference to a list of available commands
 * \param currentTurn -- pointer reference to the current player
 *
 * \returns false if a winner is found or if a player quits returns true otherwise
 */
bool playGame(DriverGameMap *& myGame, playerList & pList, comList& commands, Player *& currentTurn)
{
   map< string, int >::iterator comIT;
   string nextCommand;
   cout << "Please enter a command (lost? try 'help'): ";
   cin>>nextCommand;
   cout << endl;
   if(!cin.fail())
   {
      comIT = commands.find(nextCommand);
      if (comIT != commands.end())
      {
	 int cm = comIT->second;
	 switch(cm)
	 {
	    case 0:
	       //case 1:
	       //show help list
	       help();
	       return true; //< continue with game
	    case 1:
	       //show list of all territories
	       cout<< " >>> Listing all territories: "<<endl;
	       showmap(myGame);
	       break;
	    case 2:
	       //show a list of currentTurn players territories
	       cout<< " >>> " << currentTurn->name()<<"'s territories: "<<endl;
	       myterritories(myGame,currentTurn);
	       break;
	    case 3:
	       //play the current phase
	       cout << " >>> Playing current phase. "<<endl;
	       playPhase(myGame , pList, currentTurn);
	       //do not break here, automatically moving to next phase at end of currentPhase
	    case 4:
	       //move to the next phase
	       cout << " >>> Moving on to next phase."<<endl;
	       if(isWinner(myGame , pList, currentTurn ))
	       {
		  cout << " >>> "<<currentTurn->name() << "wins!"<<endl;
		  return false;
	       }
	       nextPhase(myGame , pList, currentTurn);
	       break;
	    case 5:
	       attack(myGame , pList, currentTurn);
	       break;
	    case 6:
	       //player quits
	       cout << " >>> "<<currentTurn->name() << " quits! (Looser!)"<< endl;
	       return false;
	    default:
	       break;
	 
	 }
      }
      else
      {
	 cout << " >>> Bad Command! \nMaybe you should type 'help' (w/o the quotes). "<<endl;
	 cout << endl;
      }
      
   }
   else{
      cout << " >>> Bad Command, can't type Today??? "<<endl;
      cin.clear();
      cout << endl;
   }
   
   
   return true;
}

/**
 * Function to check if current player is the winner
 *
 * \param g -- pointer reference to the DriverGameMap
 * \param pL -- reference to a playerList
 * \param currentTurn -- pointer reference to the current player
 *
 * \returns true if current player is the winner 
 */
bool isWinner(DriverGameMap *& g, playerList& pL, Player * currentTurn)
{
   /// \todo win condition for more than 2 players loop thru pL if all other player !alive() then currentTurn Wins
   bool win = false;
   if (pL[0]==currentTurn){
      win = !pL[1]->alive(); // \todo fix this
      territorylist us = g-> list(pL[1]);
      if (us.empty())
	 win = true;
   }
   else //(pL[1]==currentTurn)
   {
      win = !pL[0]->alive(); // \todo fix this
      territorylist us = g-> list(pL[0]);
      if (us.empty())
	 win = true;
  
   }
   return win;
}
