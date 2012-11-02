#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

class Player;
class GameMap;

typedef string PlayerName;

class Game {
  public:
   ~Game();

   //accessors
   virtaul std::vector<Player> systemPlayers() const =0;
   virtual std::vector<Player> players() const =0;
   virtual Player* winner() const =0;
   virtual Player* currentTurn() const =0;
   virtual GameMap* currentGame() const =0;
   
   //mutators
   virtual SetupGame(std::vector<PlayerName>) =0;
   
};

#endif
