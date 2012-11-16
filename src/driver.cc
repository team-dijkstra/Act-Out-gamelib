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
#include "traditionalarmy.h"

using namespace std;

typedef vector< pair< Territory*, Territory* > > adjList;
typedef vector< Player* > playerList;
typedef map< string, int > comList;
typedef Player::phaselist phaseList;
typedef set<Territory* > territorylist;


class GameMap{
public:
   GameMap(adjList & a):myAjL(a)//, unclaimed(new DefaultPlayer(string("Unclaimed")))
   {
      adjList::iterator it;
      for(it = myAjL.begin();  it!=myAjL.end() ; ++it)
      {
	 allTerr.insert(it->first);
	 allTerr.insert(it->second);
      }
   }

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

   void out(){
      cout<<"";
   }

   void print()
   {
      territorylist l = list();
      territorylist::iterator lsIT;
      for(lsIT = l.begin(); lsIT != l.end(); ++lsIT)
      {
	 cout << (*lsIT)->name() << endl;;
      }
   }

   void print(Player * p)
   {
      territorylist l = list(p);
      territorylist::iterator lsIT;
      for(lsIT = l.begin(); lsIT != l.end(); ++lsIT)
      {
	 cout << (*lsIT)->name() << endl;;
      }
      
   }
   
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
void setup(GameMap *&, playerList &, phaseList&);
void showmap(GameMap *&);
void myterritories(GameMap *&,Player *);
void playPhase(GameMap *&, playerList &, Player *&);
void nextPhase(GameMap *&, playerList &, Player *&);
void attack(GameMap *&, playerList &, Player *&);

bool playGame(GameMap *&, playerList &, comList&, Player *&);
bool isWinner(GameMap *&, playerList&, Player *);


int main()
{
   map< string, int > commands;
   
   init(commands);

   GameMap * myGameMap;
   playerList pList;
   phaseList phsList;
   phaseList::iterator phsIT;
   
   setup(myGameMap,pList,phsList);
   myGameMap->setOwners(pList[0],pList[1]);
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
   while(playGame(myGameMap, pList, commands, currentTurn));
   return 0;
}

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

void setup(GameMap *& gm ,playerList& pL, phaseList& phsL)
{
   //setup phaselist
   phsL.push_back(new DefaultPhase(string("Marshal")));
   phsL.push_back(new DefaultPhase(string("Attack")));
   phsL.push_back(new DefaultPhase(string("Redeploy")));
   
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

   gm = new GameMap(aL);
   
}

void showmap(GameMap *& g)
{
   //cout << "\t***Stub: All Territory List!" << endl;
   g->print();
   cout << endl;
}

void myterritories(GameMap *& g,Player * p)
{
   //cout << "\t***Stub: "<<p->name()<<"'s Territory List!" << endl;
   g->print(p);
   cout << endl;
}

void playPhase(GameMap *& gm, playerList & pl, Player *& player)
{
   phaseList curr = player->remainingPhases();
   phaseList::iterator cIT;
   cIT = curr.begin();
   string s = (*cIT)->name();
   gm->out();pl[0]->name();
   cout << "\t***Stub: Doing "<<player->name()<<"'s Current Phase: "<< s << endl;
   cout << endl;
}

void nextPhase(GameMap *& gm, playerList & pl, Player *& player)
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

void attack(GameMap *& g, playerList & plst, Player *& currP)
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


bool playGame(GameMap *& myGame, playerList & pList, comList& commands, Player *& currentTurn)
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

/// \todo check for winner
bool isWinner(GameMap *& g, playerList& pL, Player * currentTurn)
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
