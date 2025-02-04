#ifndef PLAINGUN_H
#define PLAINGUN_H
//#include "commons.h"
#include "usable.h"
#include "videoElementDef.h"
#include "plainMissile.h"

class plainGun : public usable, public mechanical, public collectible, public nonSteppable
{
public:
    static videoElement::videoElementDef* vd;
    virtual videoElement::videoElementDef* getVideoElementDef();
    virtual int getType();
    virtual bool use(bElem *who);
    plainGun(chamber *board);
    plainGun(chamber *board,int newSubtype);
    virtual bool mechanics();
    virtual ~plainGun();
    bool isWeapon();
    virtual bool readyToShoot();
    virtual int getAmmo();
    virtual void setAmmo(int ammo);
    virtual void setMaxEnergy(int me);
    virtual bElem* createProjectible(bElem* who);



private:
    int ammo=1+(bElem::randomNumberGenerator()%_plainGunAmmo);
    unsigned int shot=0;
   int maxEnergy=20*(1+(bElem::randomNumberGenerator()&3));

};

#endif // PLAINGUN_H
