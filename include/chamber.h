#ifndef CHAMBER_H
#define CHAMBER_H
#include "commons.h"
#include "gCollect.h"
#include "randomWordGen.h"

typedef struct color {
    int r;
    int g;
    int b;
    int a;
    } colour;
class bElem;
class gCollect;
//using boost::multi_array;
class chamber
{
    public:
        controlItem cntrlItm;
        int width;
        int height;
        coords player;
        gCollect *garbageBin;
        bElem* getElement(int x, int y);
        bElem* getElement(coords point);
        void setElement(int x, int y, bElem* elem);
        void setElement(coords point,bElem* elem);
        chamber(int x,int y);
        ~chamber();
        int getInstanceId();
        std::string getName();
        colour getChColour();

    private:
        bElem ***chamberArray;
        colour chamberColour;
        std::string chamberName;
        void setInstanceId(int id);
        int instanceid;
        static int lastid;
};

#endif // CHAMBER_H
