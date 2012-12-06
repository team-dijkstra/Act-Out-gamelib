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

#include "altdefaultgame.h"
#include "altgamemap.h"
#include "filterbyterritoryall.h"
#include "filterbyterritoryowner.h"
#include "territory.h"

using namespace std;

//globals
typedef map< string, int > commands;
typedef map< string, string > helps;

//globals
const int INT_MAX = std::numeric_limits<int>::max();

//helper classes and structs
struct ComHelp{
   commands c;
   helps h;
};

struct GameContainer {
   AltDefaultGame game;
   ComHelp coms;
   Player * currentTurn;
};

//method declarations
void preamble(); //< displays a basic overview of the game
void init_help(GameContainer&); //< initializes commands and help variables
void init_game(GameContainer&); //< initializes commands and help variables
void show_help(const ComHelp&); //< prints the help info
void get_names(vector<Game::PlayerName>&); //< gets the names of players and territories
void player_order(const GameContainer&); //< list the turn order of the players
bool play_game(GameContainer&); //< drives the game state
void show_territories(const GameContainer&); //< displays all territories, with owner and adjacencies
void play_phase(GameContainer&); //< plays the current phase
void next_phase(GameContainer&); //< moves to the next phase
void player_quits(GameContainer&); //< removes the player from the game 


void shutup_cppcheck(GameContainer& g)
{
   Player * p = g.currentTurn;
   TerritoryOperation * op = new FilterByTerritoryOwner(p->name());
   Unit::actionContainer acts = p->actions(op);
   Unit::actionContainer::iterator it = acts.begin();
   cout << (*it)->source()->name()<<endl;
   cout << (*it)->unit()->name()<<endl;
   delete op;
}

//method definitions
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
      cout <<"It is "<<game.currentTurn->name()<<"\'s turn. " 
	   <<"Type 'help' to see the list of commands again."<< endl;
      cout<<endl;
   }
   while(play_game(game));
   
   return 0;
}

void preamble()
{
   cout << "Welcome to the game."<<endl;
}

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
   
   /// \todo add check to see if they have enough players entered

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
}

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

void show_help(const ComHelp& coms) 
{
   cout << "--------------------:Help Screen:--------------------" <<endl;
   cout << "Here are the commands you can use:" <<endl <<endl;;
   //iterate through ComHelp object and display it's command and explanation
   for(helps::const_iterator it = coms.h.begin(); it != coms.h.end();++it)
      cout << it->first << " : " << it->second << endl;
   cout << "------------------:End Help Screen:------------------" <<endl;
   cout << endl;
}

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

bool play_game(GameContainer& g)
{
   //perform manditory phase setups

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
	    //cout << "entered: "<< it->first << endl; 
	    show_help(g.coms); break;
	 case 1:
	    // display all territories
	    show_territories(g);
	    cout << "entered: "<< it->first << endl;
	    break;
	 case 2:
	    // play the current turn
	    play_phase(g);
	    shutup_cppcheck(game);
	    cout << "entered: "<< it->first << endl; break;
	 case 3:
	    // move to the next turn
	    next_phase(g);
	    cout << "entered: "<< it->first << endl; break;
	 case 4:
	    //player quits
	    // player_quit(g);
	    cout << "entered: "<< it->first << endl;
	    return false;//break;
	    
      }
   }
   
   return true;
}

void show_territories(const GameContainer& g)
{
   // create filterbyt * op
   
   TerritoryOperation * op = new FilterByTerritoryAll();
   GameMap * gm = g.game.currentGame();
   
   // get Game::TerritoryList list = g.game.currentGame()->filter(op)
   
   GameMap::TerritoryList list = gm->filter(op);
   GameMap::TerritoryList adjlist;
   GameMap::TerritoryList::iterator it;
   GameMap::TerritoryList::iterator ait;

   cout << endl << endl << "List of all territories!" << endl << endl;

   // iterate thru list, displa name owner, adjacencies
   for(it = list.begin(); it != list.end(); ++it)
   {
      adjlist = gm->adjacencies(*it);
      cout << "Territory: " << (*it)->name() << "\tOwner: " << (*it)->owner()->name() 
	   << "\tAdjacent Territories: " ;
      
      // iterate thru adjacency list to print
      for(ait = adjlist.begin(); ait != adjlist.end(); ++ait)
      {
	 cout << (ait != adjlist.begin() ? ", " :"") << (*ait)->name() ;
      }
      
      cout << endl;
   }
  
   delete op;
}

void play_phase(GameContainer& g)
{
   
   cout << endl << g.currentTurn->name()<< ", Play phase" << endl;
}

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
