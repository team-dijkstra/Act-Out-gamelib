#ifndef TERRITORY_H
#define TERRITORY_H

#include <string>
#include <vector>

class Player;

class Territory {
  public:
   ~Territory();

   //accessors
   virtual Player* owner() const =0;
   virtual std::string name() const =0;
   virtual std::vector<Unit> units() const =0;

   //mutators
   virtual void owner(Player*) =0;
   
};

#endif
