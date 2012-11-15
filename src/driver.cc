/// \file
/// \brief A basic driver program for our game library -- driver.cc
//
/// Contains the main() function for implementing a basic game
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>

#include "defaultplayer.h"
#include "landterritory.h"
//#include "stlgamemap.h"

using namespace std;

typedef vector< pair< Territory*, Territory* > > adjList;
typedef vector< Player* > playerList;
typedef map< string, int > comList;


struct GameMap{
   
   GameMap(adjList){}
   void out(){cout<<"";}
   
};

void init(map< string, int > &);
void help();
void setup(GameMap *&, playerList &);
void showmap();
void myterritories(Player *);
void playPhase(GameMap *&, playerList &, Player *&);
void nextPhase(GameMap *&, playerList &, Player *&);

bool playGame(GameMap *&, playerList &, comList&, Player *&);
bool isWinner(playerList&, Player *);


int main()
{
   map< string, int > commands;
   
   init(commands);

   GameMap * myGameMap;
   playerList pList;
   
   setup(myGameMap,pList);
   Player * currentTurn;
   currentTurn = pList[0];
   cout << endl;
   help();
   cout << "Game is ready, "<< currentTurn->name() << " will proceed first" << endl<<endl;
   //cout << "The commands are: "<<endl;
   
   while(playGame(myGameMap, pList, commands, currentTurn))
   {
      cout << "The current player is: " <<currentTurn->name() <<endl;
   }
   return 0;
}

void init(map< string, int > & commands)
{
   int index = 0;
   commands["help"] = index++;
   //commands["'help'"] = index++;
   commands["showmap"] = index++;
   commands["myterritories"] = index++;
   commands["playPhase"] = index++;
   commands["nextPhase"] = index++;
   commands["quit"] = index++;
   //commands[""] = index++;
}

void help()
{
   cout << "===List Of Commands==="<<endl;
   cout << "'help': display these help instructions."<<endl;
   cout << "'showmap': display all the territories."<<endl;
   cout << "'myterritories': display the list of territories owned by the current player."<<endl;
   cout << "'playPhase': Play the current player's current phase of the current turn \n\t(will automatically move on to the next phase)"<<endl;
   cout << "'nextPhase': move to the players next phase of the current turn \n\t(if no more phases are left in the current turn, this will move to the next players turn)"<<endl;
   cout << "'quit': current player quits (lame!)"<<endl;
   cout << endl;
}

void setup(GameMap *& gm ,playerList& pL)
{
   string pn1,pn2;
   cout << "This game has 2 players"<<endl;
   cout << "Please enter the name of player 1: ";
   getline(cin, pn1);
   Player * p1 = new DefaultPlayer(pn1);
   cout << "Please enter the name of player 2: ";
   getline(cin, pn2);
   Player * p2 = new DefaultPlayer(pn2);
   pL.push_back(p1);
   pL.push_back(p2);
   
   // create territories
   Territory *t1 = new LandTerritory("Spain");
   Territory *t2 = new LandTerritory("Germany");
   Territory *t3 = new LandTerritory("GreatWhiteNorth");
   Territory *t4 = new LandTerritory("Sweden");
   Territory *t5 = new LandTerritory("StinkinYankees");
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

void showmap()
{
   cout << "\t***Stub: All Territory List!" << endl;
   cout << endl;
}

void myterritories(Player * p)
{
   cout << "\t***Stub: "<<p->name()<<"'s Territory List!" << endl;
   cout << endl;
}

void playPhase(GameMap *& gm, playerList & pl, Player *& player)
{
   gm->out();pl[0]->name();
   cout << "\t***Stub: Doing "<<player->name()<<"'s Current Phase" << endl;
   cout << endl;
}

void nextPhase(GameMap *& gm, playerList & pl, Player *& player)
{
   gm->out();pl[0]->name();player->name();
   cout << "\t***Stub: Moving to Next Phase" << endl;
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
	       showmap();
	       break;
	    case 2:
	       //show a list of currentTurn players territories
	       cout<< " >>> " << currentTurn->name()<<"'s territories: "<<endl;
	       myterritories(currentTurn);
	       break;
	    case 3:
	       //play the current phase
	       cout << " >>> Playing current phase. "<<endl;
	       playPhase(myGame , pList, currentTurn);
	       //do not break here, automatically moving to next phase at end of currentPhase
	    case 4:
	       //move to the next phase
	       cout << " >>> Moving on to next phase."<<endl;
	       nextPhase(myGame , pList, currentTurn);
	       break;
	    case 5:
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
   
   
   return isWinner( pList, currentTurn );   
}

/// \todo check for winner
bool isWinner(playerList& pL, Player * currentTurn)
{
   /// \todo win condition for more than 2 players loop thru pL if all other player !alive() then currentTurn Wins
   bool lost = currentTurn->alive(); // \todo fix this
   return lost;
}
