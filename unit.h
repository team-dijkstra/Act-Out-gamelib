#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

class Territory;
class Action;

class Unit {
  public:
   virtual ~Unit() {}

   //accessors
   virtual int increase (Unit* u) const =0;
   virtual int decrease (Unit* u) const =0;

   //mutators
   virtual int numUnits() =0;
   virtual Territory* whereAt() =0;
   virtual std::string name() =0;
   virtual std::vector<Action> actions =0;
   
};

#endif
