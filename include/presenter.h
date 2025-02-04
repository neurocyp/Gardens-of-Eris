#ifndef CHAMBERPRESENTER_H
#define CHAMBERPRESENTER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_native_dialog.h"
#include <vector>
#include <string>
#include "chamber.h"
#include "videoElementDef.h"
#include "elements.h"
#include "inputManager.h"
#include "objectTypes.h"
#include "configManager.h"
/*
 This class is responsible for menu, settings, designer and game presenter.

Trzeba utworzyć relację między obiektami, a ich wizualną reprezentacją.
Najlepiej, chcielibyśmy móc przypisywać dowolną definicję do dowolnego obiektu, problem robi się gdy:
trzeba utworzyć nowy obiekt na planszy. - można pobrac z tabeli videoElementów-lub poprosić jakiś obiekt o to.
obiekt się teleportuje (animacja)
obiekt ginie (animacja)

*/

#define _offsetX 64
#define _offsetY 64

#define _mode_onlyFloor 1
#define _mode_onlyTop   2
#define _mode_all       3





namespace presenter
{

typedef enum { MENU=0, SETTINGS=1,EDITOR=2,DEMO=3,GAME=4} presenterMode;
typedef enum { LOST=0, USERREQ=1, PAUSE=2, TELEPORTREQ=3 } _cp_gameReasonOut;



class presenter
{
public:
    presenter(chamber *board);
    ~presenter();
    bool initializeDisplay();
    int presentEverything();
    bool presentAChamber(presenterMode mod);
    bool loadCofiguredData();
    void showSplash();
    void showObjectTile(int x,int y,int offsetX,int offsetY,bElem *elem,bool ignoreOffset,int mode);
    void showText(int x,int y,int offsetX,int offsetY,std::string text);
    //relX and relY are coordinates on a board, that indicate where the player is
    void showGameField();
    ALLEGRO_EVENT_QUEUE* evQueue;
    //void showGameFieldLoop();
    void prepareStatsThing();


private:

    ALLEGRO_FONT* myfont;
    std::string splashFname;
    inputManager* inpMngr;
    int sWidth;
    int sHeight;
    int scrHeight;
    int scrWidth;
    int spacing;
    int scrTilesX;
    int scrTilesY;
    coords previousPosition;
    coords positionOnScreen;

    ALLEGRO_BITMAP* internalBitmap;
    ALLEGRO_BITMAP* statsStripe;
    int bsHeight,bsWidth;
    _cp_gameReasonOut presentGamePlay();
    chamber *_cp_attachedBoard;
    ALLEGRO_TIMER* alTimer;
    // ALLEGRO_TIMER* scrTimer;

    ALLEGRO_DISPLAY* display;

    ALLEGRO_BITMAP *sprites;
    typedef struct movingSprite
    {
        int x;
        int y;
        bElem* elem;

    } movingSprite;



};

#endif // CHAMBERPRESENTER_H
}
