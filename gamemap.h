#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

class Player;
class Territory;

typedef string TerritoryName;
typedef string operation; //<-just for now will properly define opeations later

class GameMap {
  public:
   virtual ~GameMap() {}

   //accessors
   virtual Territory find(TerritoryName) const =0;
   virtual std::vector<Territory> adjacencies(Territory *) const =0;
   virtual std::vector<Territory> players(Player *) const =0;

   //mutators
   virtual void traverse(operation, Territory * start) =0;
   
};

#endif
