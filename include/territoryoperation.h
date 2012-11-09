#ifndef TERRITORYOPERATION_H
#define TERRITORYOPERATION_H

class Territory;

class TerritoryOperation {
  public:
   virtual ~TerritoryOperation() {}
   //mutators
   virtual bool operator()(Territory *) =0; 
   
};

#endif
