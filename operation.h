#ifndef OPERATION_H
#define OPERATION_H

class Territory;

class Operation {
  public:
   virtual ~Operation {}
   //mutators
   virtual bool doaction(Territory) =0; 
   
};

#endif
