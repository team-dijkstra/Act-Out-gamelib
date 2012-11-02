#ifndef ACTION_H
#define ACTION_H

class Action {
   virtual void do(int nUnits,Territory T)=0;
   virtual String name()=0;
   virtual bool applicable(Phase p)=0;
};

#endif
