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
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <cctype>
#include <iomanip>

#include "altdefaultgame.h"
#include "altgamemap.h"
#include "filterbyterritoryall.h"
#include "filterbyterritoryowner.h"
#include "filterbyterritoryname.h"
#include "filterbyallunittypes.h"

#include "territory.h"
#include "action.h"
#include "takeoverop.h"
#include "phase.h"
#include "config.h"

#include "debug.h"

using namespace std;

//globals
typedef map< string, int > commands; ///< map of strings and integers used for the commands
typedef map< string, string > helps; ///< map of strings for help messages

//globals
const int INT_MAX = std::numeric_limits<int>::max(); ///< global constant of the maximum number stored by and int
const int DISTRIBUTE_TERRITORIES = 1; ///< global constant of the number of territorries to distribute to each player upon GameMap setup
const int SPECIAL_FORCES = 3; ///< global constant of the number of traditional armies each Player receives at the start of their turn
const int INIT_TERRITORIES = 1; ///< global constant of the number of territorries to distribute to each player at the start of their turn

//helper classes and structs

/// Stores commands and help info
struct ComHelp{
   commands c; ///< map of valid commands
   helps h; ///< map of help messages
};

/// Stores some global driver level checks
struct Parametrics {
   /// sets seen_marshal to false
   Parametrics(): seen_marshal(false)
   {} 
   bool seen_marshal; ///< whether the Marshal Phase has been executed
};

/// Stores the Game state
struct GameContainer {
   AltDefaultGame game; ///< current Game
   ComHelp coms; ///< help messages and commands
   Player * currentTurn; ///< the Player whose turn it is.
   Parametrics checks; ///< the Parametrics object for checking
};

//method declarations
void preamble(); ///< displays a welcome message
void init_help(GameContainer&); ///< initializes commands and help variables
void init_game(GameContainer&); ///< initializes commands and help variables
void show_help(const ComHelp&); ///< prints the help info
void get_names(vector<Game::PlayerName>&); ///< gets the names of players and territories
void player_order(const GameContainer&); ///< list the turn order of the players
bool play_game(GameContainer&); ///< drives the game state
void show_territories(const GameContainer&); ///< displays all territories, with owner and adjacencies
void play_phase(GameContainer&); ///< plays the current phase
void next_phase(GameContainer&); ///< moves to the next phase
void player_quits(GameContainer&); ///< removes the player from the game
void manditory_phase_setup(GameContainer&); ///< run manditory phase setup actions
void setup_marshal(GameContainer&,int,Player*); ///< assigns unclaimed territories
void display_actions(GameContainer&,string);  ///< display the available actions 
void do_marshal(GameContainer&);  ///< execute the marshal phase
void do_attack(GameContainer&);  ///< execute the attack phase
void do_redeploy(GameContainer&);  ///< execute the redeploy phase
void choose_actions(GameContainer&,string);  ///< pick and execute from the available actions 
void show_adjacencies(const GameContainer&, const Territory *); ///< displays adjacent territory names
void do_action(GameContainer&, Unit::actionContainer &, Territory * ); ///< execute the action

//method definitions

/// Main function that runs the game
int main()
{
   preamble();
   
   //create game container
   GameContainer game;
   
   //setup the help and commands
   init_help(game);

   //initialize
   init_game(game);

   //print basic game info
   player_order(game);
   show_help(game.coms);

   //play the game
   do
   {
      Phase* currPhase = game.currentTurn->remainingPhases()[0]; //get the current phase
      cout <<"It is the *"<< currPhase->name() <<"* phase on "<<game.currentTurn->name()<<"\'s turn. " 
	 //<<"Enter a command. \n\t(Type 'help' to see the list of commands again.): "
	   << endl;
      cout<<endl;
   }
   while(play_game(game));

   // shutup_cppcheck(game);

   return 0;
}

void preamble()
{
   cout << "Welcome to the game."<<endl;
}

/// \param g -- the GameContainer passed by reference to permit access to required Game information
void init_help(GameContainer& g)
{
   //setup commands and help info
   string command, explanation;
   int index = 0;

   command = "help";
   explanation = "Display these help instructions.\n";
   g.coms.c[command] = index++;
   g.coms.h[command] = explanation;

   command = "maps";
   explanation = "Display all the territories, their owner, and the adjacent territories.\n";
   g.coms.c[command] = index++;
   g.coms.h[command] = explanation;

   command = "play";
   explanation = "Play the current phase of the current player's turn.\n\t(will automatically move on to the next phase)\n";
   g.coms.c[command] = index++;
   g.coms.h[command] = explanation;
      
   command = "next";
   explanation = "Move to the next phase of the current player's turn \n\t(if no more phases are left in the current turn, this will move to the next players turn)\n\tN.B. Only use it you want to skip doing anything this current phase!!!\n";
   g.coms.c[command] = index++;
   g.coms.h[command] = explanation;
   
   command = "quit";
   explanation = "Current player quits (lame!)\n";
   g.coms.c[command] = index++;
   g.coms.h[command] = explanation;

   return ;
}

/// @copydoc init_help
void init_game(GameContainer& g)
{
   vector<Game::PlayerName> players, territories;
   
   cout << "Enter player names, 1 per line: (push Ctrl+d when done)"<<endl;
   while(players.size()<2) //ensure at least 2 players
   {
      get_names(players);
      if (players.size()<2)
	 cout << "You can't play with yourself!!!! Enter more players." << endl;
   }
   
   cout << "Enter territory names, 1 per line: (push Ctrl+d when done)"<<endl;
   while(territories.size() < (players.size()*3) )
   {
      get_names(territories);
      if (territories.size()< (players.size()*3) )
	 cout << "Not enough land!!!! Enter more territories." << endl;
   }

   cout << "There are " << players.size()
	<< " players, and " << territories.size()
	<< " territories." << endl
	<< "Setting up game ..." << endl
	<< endl;

   //setup the game object
   g.game.setupGame(players, territories);
   
   //set the current turn to the first player in the playerlist
   Game::playerlist list = g.game.players();
   Game::playerlist::const_iterator it = list.begin();
   g.currentTurn = (*it);

   //GameMap* gMap = g.game.currentGame();
   for(;it!=list.end();++it)
      setup_marshal(g,INIT_TERRITORIES,(*it) );
}

/// \param namelist -- list of strings to be set as the names of the players
void get_names(vector<Game::PlayerName>& namelist)
{
   string name;
   getline(cin,name);
   
   while(!cin.fail() && !name.empty())
   {
      vector<Game::PlayerName>::iterator it = find(namelist.begin(), namelist.end(), name);
      if(it == namelist.end())
	 namelist.push_back(name);
      else
	 cout << "You goofed! You used that name already. \n(Try again with a unique name!):"<<endl;
      getline(cin,name);
   } 
   cin.clear();
}

/// \param coms -- the ComHelp passed by reference to permit access to required help screen information
void show_help(const ComHelp& coms) 
{
   cout << "--------------------:Help Screen:--------------------" <<endl;
   cout << "Here are the commands you can use:" <<endl <<endl;;
   //iterate through ComHelp object and display it's command and explanation
   for(helps::const_iterator it = coms.h.begin(); it != coms.h.end();++it)
      cout << it->first << " : " << it->second ;//<< endl;
   cout << "------------------:End Help Screen:------------------" <<endl;
   cout << endl;
}

/// @copydoc init_help
void player_order(const GameContainer& g) 
{
   cout << "The players' turn order is: " <<endl;
   Game::playerlist list = g.game.players();
   for(Game::playerlist::const_iterator it = list.begin(); it != list.end(); ++it)
   {
      cout << (*it)->name() << endl;
   }
   cout << endl;
}

/// @copydoc init_help
/// \return whether the Game continues
bool play_game(GameContainer& g)
{
   //perform manditory phase setups & checks
   manditory_phase_setup(g);

   //get user command and execute
   cout << "Please enter a command (lost? try 'help'): ";
   string nextCommand;
   cin>>nextCommand;

   //cout << INT_MAX;
   while (cin.fail() || nextCommand.empty() )
   {
    
      cout << " >>> Bad Command, can't type Today??? \nTry again: "<<endl;
      cin.clear(); cin.ignore(INT_MAX,'\n');
      cout << endl;
      cin>>nextCommand;
      cout << nextCommand;
   }
   
   commands::iterator it = g.coms.c.find(nextCommand);
   if (it ==  g.coms.c.end() )
   {
      cout << " >>> Bad Command! \nMaybe you should type 'help' (w/o the quotes). "<<endl;
      cout << endl;
   }
   else
   {
      //cout << it->second << endl;
      switch (it->second)
      {
	 case 0:
	    cout << endl;//<<"entered: "<< it->first << endl; 
	    show_help(g.coms); break;
	 case 1:
	    // display all territories
	    show_territories(g);
	    //cout << "entered: "<< it->first << endl;
	    break;
	 case 2:
	    // play the current turn
	    play_phase(g);
	    //cout << "entered: "<< it->first << endl; //continues automatically to next phase
	 case 3:
	    // move to the next turn
	    next_phase(g);
	    cout << "entered: "<< it->first << endl; break;
	 case 4:
	    //player quits
	    player_quits(g);
	    cout << "Player: "<<g.currentTurn->name()<< it->first << endl;
	    break;
	    return false;//break;
	    
      }
   }
   
   return true;
}

/// @copydoc init_help
void show_territories(const GameContainer& g)
{
   // create 
   
   //TerritoryOperation * op = new FilterByTerritoryAll();
   FilterByTerritoryAll op;
   GameMap * gm = g.game.currentGame();
   
   // get Game::TerritoryList list = g.game.currentGame()->filter(op)
   
   GameMap::TerritoryList list = gm->filter(&op);
   
   GameMap::TerritoryList::iterator it;
   
   cout << "\n--------------------:Territory Screen:--------------------" <<endl;
   //cout << endl << endl << "List of all territories!" << endl << endl;

   // iterate thru list, displa name owner, adjacencies
   for(it = list.begin(); it != list.end(); ++it)
   {
      cout << "Territory: " << (*it)->name() << " has ";

      //loop through units and display
      //UnitOperation * filter = new FilterByAllUnitTypes();
      FilterByAllUnitTypes filter;
      Territory::unitContainer armies = (*it)->units(&filter);
      //delete filter;
      for(Territory::unitContainer::iterator uIT = armies.begin(); uIT != armies.end(); ++uIT)
      {
	 // list " numUnits() of Unit->name() "
	 cout << (uIT)->second->numUnits() << " units of " << (uIT)->second->name() <<" ";
      }
      cout <<"\tOwner: " << (*it)->owner()->name() 
	   << "\tAdjacent Territories: " ;

      show_adjacencies(g, *it );
     
      
      cout << endl;
      
   }
   cout << "------------------:End Territory Screen:------------------" <<endl;
   //delete op;
}

/// @copydoc init_help
void play_phase(GameContainer& g)
{
   //check phase
   Phase* currPhase = g.currentTurn->remainingPhases()[0]; //get the current phase
   cout << "\n------>current phase: " << currPhase->name() << endl;
   cout << g.currentTurn->name()<< ", Play phase" << endl;
   if (currPhase->name() == phase::MARSHAL)
   {

      //call do_marshal(g);
      //cout << "PLAY !===!!!!--IN MARSHAL PHASE--!!!============!"<<endl;
      do_marshal(g);
   }
   else if (currPhase->name() == phase::ATTACK)
   {
      //call do_attack(g);
      //cout << "PLAY !===!!!!--IN ATTACK PHASE--!!!============!"<<endl;
      do_attack(g);
   }
   else if (currPhase->name() == phase::REDEPLOY)
   {
      //call do_redeploy(g);
      //cout << "PLAY !===!!!!--IN REDEPLOY PHASE--!!!============!"<<endl;
      do_redeploy(g);
   }
   else
   {
      cout << "PLAY !===!!!!--ERROR ::not in a known Phase:: ERROR--!!!============!"<<endl;
   }
   
}

/// @copydoc init_help
void next_phase(GameContainer& g)
{
   cout << endl << "next phase" << endl;
   //g.currentTurn->remainingPhases();
   //cout<<endl<<currentTurn();
   bool nextPlayer = g.currentTurn->nextPhase();
   
   //shift thru phases
   if(nextPlayer)
   {
      
      AltDefaultGame::playerlist pls = g.game.players();
      AltDefaultGame::playerlist::iterator it = find( pls.begin(), pls.end(), g.currentTurn);
      ++it;
      if(it == pls.end())
      {
	 //if there is no next player
	 it = pls.begin();
      }
      cout << "current Player: " << g.currentTurn->name() <<endl
	   << "next Player: " << (*it)->name() <<endl;

      g.currentTurn = *it;
    
   }
}

/// @copydoc init_help
void player_quits(GameContainer& g)
{
   Player * sysp = g.game.systemPlayers()[0];
   GameMap* gMap = g.game.currentGame();
   //TakeOver<int> op2(p);
   FilterByTerritoryOwner op(g.currentTurn->name());
   GameMap::TerritoryList list = gMap->filter(&op);
   for( GameMap::TerritoryList::iterator it = list.begin(); it != list.end(); ++it)
      (*it)->owner(sysp);
}

/// @copydoc init_help
void manditory_phase_setup(GameContainer& g)
{
   //check phase
   Phase* currPhase = g.currentTurn->remainingPhases()[0]; //get the current phase

   if (currPhase->name() == phase::MARSHAL)
   {
      //protects against errors allowing setup_marshal to be called more than once per turn
      if(!g.checks.seen_marshal)
      {
	 //call setup_marshal(g);

	 setup_marshal(g,DISTRIBUTE_TERRITORIES, g.currentTurn);
	 //cout <<" I havent seen the Marshal phase yet!!"<<endl;
	 //cout << "Manditory !===!!!!--IN MARSHAL PHASE--!!!============!"<<endl;
	 g.checks.seen_marshal = true;
      }
      // else
      // { //debug
      // 	 cout <<" I've seen this Marshal phase .......MOVING ON!!"<<endl;
      // }
   }
   else if (currPhase->name() == phase::ATTACK)
   {
      //reset  g.checks.seen_marshal for the next turn
      g.checks.seen_marshal = false;
      //cout << "Manditory !===!!!!--IN ATTACK PHASE--!!!============!"<<endl;
   }
   else if (currPhase->name() == phase::REDEPLOY)
   {
      //cout << "Manditory !===!!!!--IN REDEPLOY PHASE--!!!============!"<<endl;
   }
   else
   {
      cout << "Manditory !===!!!!--ERROR ::not in a known Phase:: ERROR--!!!============!"<<endl;
   }
}

/// @copydoc init_help
/// \param n -- the number of territories assigned to each Player at the beginning of each turn
/// \param p -- the Player whose turn it is
void setup_marshal(GameContainer& g, int n, Player * p)
{
   //cout << "Setting up the "<<phase::MARSHAL<< " phase:"<<endl;
   Player * sysp = g.game.systemPlayers()[0];
   //if any unclaimed territories, give the client up to n territories

   //get all territories
   GameMap * gmap = g.game.currentGame();
   //TerritoryOperation * op = new FilterByTerritoryAll();
   FilterByTerritoryAll op;
   GameMap::TerritoryList list = gmap->filter(&op);

   //cout <<"check: setup_marshal()"<<endl;
   for(GameMap::TerritoryList::iterator it = list.begin(); it != list.end(); ++it)
   {
      //cout <<"check: setup_marshal() ... in for loop"<<endl;
      Territory * t = *it;
      //cout << "Territory: "<<t->name() <<", Owner:"<< t->owner()->name()<<endl;
      if ( t->owner()->name() == sysp->name() && n > 0)
      {
	 cout << "Assigning " << p->name() << " the "
	      << t->name() << " territory"<<endl;
	 t->owner(p);
	 //UnitOperation * filter = new FilterByAllUnitTypes();
	 FilterByAllUnitTypes filter;
	 Territory::unitContainer armies = t->units(&filter);
	 //delete filter;
	 Territory::unitContainer::iterator it = armies.find("BuilderUnit");
	 Unit::actionContainer acts = (it->second)->actions();
	 acts[0]->doaction(1,t);
	 //cout <<"check: setup_marshal() ... in if"<<endl;
	 //cout <<"check, n="<<n<<endl;
	 --n;
      }
   }

   //delete op;
   //g.currentTurn->name();
}

/// @copydoc init_help
void do_marshal(GameContainer& g)
{
   

   cout << "You get to add "<<SPECIAL_FORCES<<" armies"<<endl;

   for (int i = 0; i<SPECIAL_FORCES;++i)
   {
      display_actions(g, phase::MARSHAL);
      cout<<"Place army #"<<i+1<<" of "<<SPECIAL_FORCES<<endl;
      string message = "What territory would you like to place this army on? ";
      choose_actions(g, message);
      show_territories(g);
   }
}

/// @copydoc init_help
void do_attack(GameContainer& g)
{

   cout << "Choose your attacks" << endl;
   while(true)
   {
      display_actions(g, phase::ATTACK);
      string yn;
      do
      {
	 cout << "Would you like to attack (y/n)?: " << flush;
	 cin >> yn;
     
      }while(yn != "y" && yn != "yes" && yn != "n" && yn != "no");

      
      if(yn == "y" || yn =="yes")
      {
	 string message = "What terrritory would you like to attack from? ";
	 choose_actions(g, message);
	 show_territories(g);
      }
      else
	 return;
   }
}

/// @copydoc init_help
void do_redeploy(GameContainer& g)
{
   
   cout << "Choose your Redeployments" << endl;
   while(true)
   {
      display_actions(g, phase::ATTACK);
      string yn;
      do
      {
	 cout << "Would you like to redeploy (y/n)?: " << flush;
	 cin >> yn;
     
      }while(yn != "y" && yn != "yes" && yn != "n" && yn != "no");
   
      if(yn == "y" || yn =="yes")
      {
	 string message = "What terrritory would you like to redeploy from? ";
	 choose_actions(g, message);
	 show_territories(g);
      }
      else
	 return;
   }
}

/// @copydoc init_help
/// \param cPhase -- the name of the current Phase
void display_actions(GameContainer& g, string cPhase)
{
   //display actions:
   cout << "--------------------:Action Screen:--------------------"<<endl;
   cout << "Here are your available actions for this phase: " <<endl;
   //get current player's availible actions.
   Player * p = g.currentTurn;
   //TerritoryOperation * op1 = new FilterByTerritoryOwner(p->name());
   FilterByTerritoryOwner op1(p->name());
   Unit::actionContainer acts = p->actions(&op1);
   //delete op1;
   //iterate thru actions and display info
   for(Unit::actionContainer::iterator it = acts.begin(); it != acts.end(); ++it)
   {
      cout <<"From Territory: "<< (*it)->source()->name() << ", using the " << (*it)->unit()->name()
	   << ", you can " << (*it)->name();
      if( cPhase == phase::MARSHAL)
      {
	 cout << " on " <<  (*it)->source()->name();
      }
      else if (cPhase == phase::ATTACK)
      {
	 cout << " on one of these territories: ";
	 show_adjacencies(g, (*it)->source() );
      }
      else if (cPhase == phase::REDEPLOY)
      {

      }
      else
      {
	 cout << "error unknown phase!";
      }
      cout << endl;
   }
   cout << "------------------:End Action Screen:------------------"<<endl;
}

/// @copydoc init_help
/// \param t - the Territory for which to show adjacencies
void show_adjacencies(const GameContainer& g, const Territory * t )
{
   GameMap * gm = g.game.currentGame();
   GameMap::TerritoryList adjlist = gm->adjacencies(t);
   // iterate thru adjacency list to print
   for(GameMap::TerritoryList::const_iterator ait = adjlist.begin(); ait != adjlist.end(); ++ait)
   {
      cout << (ait != adjlist.begin() ? ", " :"") << (*ait)->name() ;
   }
   
}

/// \param check -- the current Phase name
/// \param p -- the Player which is compared to the owner of t
/// \param t -- the Territory whose owner is compared to p
/// \return whether the comparison passed
bool check_owner(string check, Player * p , Territory * t)
{
   //Phase* currPhase = p->remainingPhases()[0]; //get the current phase
   if (check == phase::MARSHAL)
   {
      return (p->name() == t->owner()->name());
   }
   else if (check == phase::ATTACK)
   {
      return (p->name() != t->owner()->name());
   }
   else if (check == phase::REDEPLOY)
   {
      return (p->name() == t->owner()->name());
   }
   else
   {
      cout << "!===!!!!--ERROR ::not in a known Phase:: ERROR--!!!============!"<<endl;
      return false;
   } 
   return false;
}

/// @copydoc init_help
/// \param message -- the output displayed to request the name of a Territory
/// \param acts -- the container of actions to display after applying the filter
/// \param check -- comparison string to be passed to the check_owner function
/// \return the Territory to either execute or receive an Action
Territory* ask_territory(GameContainer& g, string message, Unit::actionContainer & acts, string check)
{
    Player * p = g.currentTurn;
   AltGameMap::TerritoryList tlist;
   AltGameMap::TerritoryList::iterator lit;

   string nm;
   bool valid_territory = false;
  
   cout<<message<<endl;
   while(tlist.empty() || !valid_territory)
   {
     
      //getline(cin,nm);
      cin >> nm;
      FilterByTerritoryName filter(nm);
      //TerritoryOperation * filter = new FilterByTerritoryName(nm);
     
      tlist = g.game.currentGame()->filter(&filter);

//      dout << "tlist empty? " << boolalpha << tlist.empty() << " valid_territory=" << valid_territory << endl; 
      if(!tlist.empty())
      {
	 lit = tlist.begin();
	 //if(p->name() == (*lit)->owner()->name())
	 valid_territory = check_owner(check, p , *lit);
	 if(valid_territory)
	 {
	    acts = p->actions(&filter);
	    break;
	 }
	 else
	    cout << endl << "Not an acceptable territory!" << endl << message; 
      }

	 
      //delete filter;
   }

   return *lit;
}

/// @copydoc init_help
/// \param message -- the string passed to the ask_territory function
void choose_actions(GameContainer& g, string message)
{

   //cout << endl << message <<endl;
   //Player * p = g.currentTurn;    
   Unit::actionContainer acts;
   Territory * t = ask_territory(g, message, acts, phase::MARSHAL );
    
   do_action(g, acts, t );
   
}

/// @copydoc init_help
/// \param from -- the Territory from which to find 'to' as an adjacent Territory
/// \param to -- the Territory for which to be found as an adjacent Territory ofthe from Territory
/// \return whether 'to' is adjacent to from
bool is_adjacent(GameContainer& g, Territory * from, Territory * to)
{
   GameMap * gMap = g.game.currentGame();
   GameMap::TerritoryList adjs = gMap->adjacencies(from);
   GameMap::TerritoryList::iterator it = find(adjs.begin(),adjs.end(),to);

   return (it != adjs.end() );
}

/// @copydoc init_help
/// \param acts -- the container consisting of one Action to be executed
/// \param from -- the Territory that is performing the Action
void do_action(GameContainer& g, Unit::actionContainer & acts, Territory * from)
{
   Unit::actionContainer::iterator it = acts.begin();
   Phase* currPhase = g.currentTurn->remainingPhases()[0]; //get the current phase   
   
   if (currPhase->name() == phase::MARSHAL)
   {
      (*it)->doaction(1, from);
      cout<<(*it)->status()<<endl;
      (*it)->setState();
   }
   else if (currPhase->name() == phase::ATTACK)
   {
      //ASK WHAT TERRITORY TO
      Unit::actionContainer actsOn;
      string message = "What territory do you want to attack? ";
      Territory * to = ask_territory(g, message, actsOn , phase::ATTACK);
      //check for adjacency
      if(is_adjacent(g,from,to))
      {
	 (*it)->doaction(1, to);
	 cout<<(*it)->status()<<endl;
	 (*it)->setState();
      }
   }
   else if (currPhase->name() == phase::REDEPLOY)
   {
      //ASK WHAT TERRITORY TO
      Unit::actionContainer actsOn;
      string message = "What territory do you want to redeploy to? ";
      Territory * to = ask_territory(g, message, actsOn , phase::REDEPLOY);
      //check for adjacency
      if(is_adjacent(g,from,to))
      {
	 (*it)->doaction(1, to);
	 cout<<(*it)->status()<<endl;
	 (*it)->setState();
      }
   }
   else
   {
      cout << "PLAY !===!!!!--ERROR ::not in a known Phase:: ERROR--!!!============!"<<endl;
   } 
   
}
