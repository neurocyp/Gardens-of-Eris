#include "plainMissile.h"


videoElement::videoElementDef* plainMissile::vd=nullptr;
plainMissile::plainMissile(chamber *mychamber) : killableElements(mychamber), movableElements(mychamber), mechanical(mychamber)
{
    this->statsOwner=nullptr;
    this->setStats(new elemStats(_plainMissileEnergy));
    this->setEnergy(_plainMissileEnergy);
    this->setMoved(0);
    this->setWait(_plainMissileSpeed);
    this->setDirection(UP);
    this->setMoved(0);
    this->setSubtype(0);
}
plainMissile::plainMissile(chamber* mychamber, int energy) : killableElements(mychamber),  movableElements(mychamber), mechanical(mychamber)
{
    this->statsOwner=nullptr;
    this->setStats(new elemStats(energy));
    this->setEnergy(energy);
    this->setMoved(0);
    this->setWait(_plainMissileSpeed);
    this->setDirection(UP);
    this->setMoved(0);
    this->setSubtype(0);
}

plainMissile::~plainMissile()
{
    if(this->statsOwner!=nullptr)
    {
        this->statsOwner->unlockThisObject(this);
        this->statsOwner=nullptr;
    }
    //dtor
}
int plainMissile::getType()
{
    return _plainMissile;
}

void plainMissile::stomp(bElem* who)
{
    bElem::stomp(who);
    if(who->getType()!=this->getType())
    {
        who->hurt(this->getEnergy());
        this->disposeElement();
    }
    return;
}


videoElement::videoElementDef* plainMissile::getVideoElementDef()
{
    return plainMissile::vd;
}
bool plainMissile::setEnergy(int points)
{
    if(this->statsOwner!=nullptr && this->statsOwner->getStats()!=nullptr)
    {
        int ep=(points*4)/(_dexterityLevels+1-this->statsOwner->getStats()->getDexterity());
        int dp=points-ep;
        int r=this->randomNumberGenerator()%(points+1);
        mechanical::setEnergy(((r<=dp)?ep/2:ep)+1);
    } else
        mechanical::setEnergy(points);
    return true;
}


bool plainMissile::mechanics()
{
    bool res;
    int mvd=this->getMoved();
    res=killableElements::mechanics();
    if(!res) return false;
    if(this->isDying())
        return true;
    if (this->getMoved()==0 && mvd==0)
    {
        bElem *myel=this->getElementInDirection(this->getDirection());
        if(myel==nullptr || myel->isDying() || myel->isTeleporting() || myel->isDestroyed())
        {
            this->disposeElement();
            return true;
        }
        if (myel->isSteppable()==true)
        {
            this->moveInDirectionSpeed(this->getDirection(),_plainMissileSpeed);
            return true;
        }
        if (myel->canBeKilled()==true)
        {
 /*           if (myel->getType()==this->getType() && myel->getDirection()==this->getDirection() && myel->getSubtype()==this->getSubtype() && !myel->isDestroyed() && !myel->isDying())
            {
                return true;
            }
 */
            myel->hurt(this->getEnergy());
            if(this->statsOwner!=nullptr && this->statsOwner->getStats()!=nullptr)
            {
                this->statsOwner->getStats()->countHit(myel);
            }
            if(!myel->isDying() && !myel->isDestroyed())
            {
                this->kill();
            }
            else
            {
                if(this->statsOwner!=nullptr && this->statsOwner->getStats()!=nullptr)
                {
                    this->statsOwner->getStats()->countKill(myel);
                }
                if (!this->isDying())
                    this->disposeElement();
            }
            return true;
        }
        if(myel->isDying()|| myel->isDestroyed()) // if next element in path is already dying, just disappear.
            this->disposeElement();
        this->kill();
        return true;
    }
    return res;
}
void plainMissile::setStatsOwner(bElem* owner)
{
    if(owner!=nullptr)
    {
        this->statsOwner=owner;
        this->setEnergy(this->getEnergy());

    }
}



