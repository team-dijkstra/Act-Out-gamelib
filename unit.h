#ifndef ___UNIT_H
#define ___UNIT_H

class Unit {
   //accessors
   int increase (Unit u) =0;
   int decrease (Unit u) =0;

   //mutators
   int numUnits() =0;
   Territory whereAt() =0;
   String name() =0;
   List<Action> actions =0;
   
};
