#ifndef OPERATION_H
#define OPERATION_H

class Territory;

class Operation {
  public:
   virtual ~Operation {}
   //mutators
   virtual bool operator()(Territory *) =0; 
   
};

#endif
