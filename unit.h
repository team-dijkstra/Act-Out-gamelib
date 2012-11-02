#ifndef UNIT_H
#define UNIT_H

class Unit {
   //accessors
   virtual int increase (Unit u) =0;
   virtual int decrease (Unit u) =0;

   //mutators
   virtual int numUnits() =0;
   virtual Territory whereAt() =0;
   virtual String name() =0;
   virtual List<Action> actions =0;
   
};

#endif
