#ifndef OPERATION_H
#define OPERATION_H

class Operation {
  public:
   virtual ~Operation {}
   //mutators
   virtual bool do(Territory) =0; 
   
};

#endif
