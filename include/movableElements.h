#ifndef MOVABLEELEMENTS_H
#define MOVABLEELEMENTS_H

#include "nonSteppable.h"
#include "commons.h"
#include "objectTypes.h"
#include "videoElementDef.h"

#include "chamber.h"
#include "gCollect.h"
//#include "objectTypes.h"



class movableElements :  virtual  public bElem
{
    public:
        virtual videoElement::videoElementDef* getVideoElementDef();
        static videoElement::videoElementDef* vd;
        movableElements(chamber *board);
        virtual ~movableElements();
        virtual bool isMovable();
        virtual bool moveInDirection(direction dir);
        virtual bool moveInDirectionSpeed(direction dir,int speed);
        virtual int getType();
        virtual bool canPush();
        virtual void setMoved(int time);
        virtual int getMoved();
        virtual bool dragInDirection(direction dragIntoDirection);
        virtual coords getOffset();
        void setMovable(bool m);
        void setCanPush(bool sp);
        direction facing;

    private:
        bool movable=true;
        unsigned int _me_moved=0;
        int movingTotalTime=0;
        bool _me_canPush=true;

};

#endif // MOVABLEELEMENTS_H
