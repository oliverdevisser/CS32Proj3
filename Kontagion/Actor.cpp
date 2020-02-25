#include "StudentWorld.h"
#include "GameWorld.h"
#include "Actor.h"
#include <algorithm>


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int ImageID, double startX, double startY, StudentWorld* worldPointer, Direction dir, int depth, double size)
    : GraphObject(ImageID, startX, startY, dir, depth, size)
{
    m_worldPointer = worldPointer;
    setDamage(0);
    isBlock(false);
}

// -------------------- ACTOR BASE CLASSES ---------------------------

Socrates::Socrates(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Actor(IID_PLAYER, startX, startY, gameWorld, dir, depth, size)
{
    setHitpoints(100);
    isAlive(true);
    setSprays(20);
    setFlames(100);
    isBlock(false);
    isDamageable(true);
}

void Socrates::doSomething(){
    if (getHitpoints() <= 0)
        return;
    int ch;
    double x = getX();
    double y = getY();
    if (getWorldPointer()->getKey(ch)){
        switch (ch){
            case KEY_PRESS_LEFT:
                this->setDirection(this->getDirection() + 5);
                moveSocrates(this->getDirection());
                break;
            case KEY_PRESS_RIGHT:
                this->setDirection(this->getDirection() - 5);
                moveSocrates(this->getDirection());
                break;
            case KEY_PRESS_SPACE:
                if (getSprays() > 0){
                    getPositionInThisDirection(this->getDirection(), SPRITE_WIDTH, x, y);
                    getWorldPointer()->addActorToList(new Spray(x, y, getWorldPointer(), this->getDirection()));
                    setSprays(getSprays() - 1);
                    getWorldPointer()->playSound(SOUND_PLAYER_SPRAY);
                }
                break;
            case KEY_PRESS_ENTER:
                if (getFlames() > 0){
                    for (int i = 0; i < 16; i++){
                        getPositionInThisDirection(22 * i, SPRITE_WIDTH, x, y);
                        getWorldPointer()->addActorToList(new Flame(x, y, getWorldPointer(), 22 * i));
                    }
                    setFlames(getFlames() - 1);
                    getWorldPointer()->playSound(SOUND_PLAYER_FIRE);
                }
                break;
        }
    } else {
        if (getSprays() < 20){ //no key is pressed
            setSprays(getSprays() + 1);
        }
    }
    
    //Other cases
    
    for (int i = 0; i < getWorldPointer()->getActorListSize(); i++){
        if (overlap(this, getWorldPointer()->getActor(i))){
            if (getWorldPointer()->getActor(i)->isDamageable()){
                setHitpoints(getHitpoints() - getWorldPointer()->getActor(i)->getDamage());
                getWorldPointer()->getActor(i)->isAlive(false);
            }
            if (getHitpoints() > 0){
                getWorldPointer()->playSound(SOUND_PLAYER_HURT);
            } else {
                isAlive(false);
                getWorldPointer()->playSound(SOUND_PLAYER_DIE);
            }
        }
    }
    //Doesn't block other actors
    
    return;
}

void Socrates::moveSocrates(int dir){
    const double PI = 4 * atan(1);
    dir = (180 + dir) % 360;
    
    double newX = (VIEW_RADIUS +  cos(dir * (PI / 180)) * VIEW_RADIUS);
    double newY = (VIEW_RADIUS +  sin(dir * (PI / 180)) * VIEW_RADIUS);

    //std::cout << newX << " " << newY;
    moveTo(newX, newY);
    increaseAnimationNumber();
}

Bacteria::Bacteria(int ImageID, double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Actor(ImageID, startX, startY, gameWorld, dir, depth, size)
{
    setPlanDist(0);
    isAlive(true);
    gameWorld->setNumBacteria(gameWorld->getNumBacteria() + 1);
    isDamageable(true);
}

void Bacteria::doSomething(){
    
}

Goodies::Goodies(int ImageID, double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Actor(ImageID, startX, startY, gameWorld, dir, depth, size)
{
    isAlive(true);
    setHitpoints(0);
    setLifetime(std::max(randInt(0, 300 - 10 * getWorldPointer()->getLevel() - 1), 50));
    isDamageable(false);
}

void Goodies::doSomething(){
    
}

Projectile::Projectile(int ImageID, double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Actor(ImageID, startX, startY, gameWorld, dir, depth, size)
{
    isDamageable(false);
    setDistTravelled(SPRITE_WIDTH);
    isBlock(false);
}

void Projectile::doSomething(){
    if (isAlive() == false)
        return;
    for (int i = 1; i < getWorldPointer()->getActorListSize(); i++) { //don't check for socrates
        if (overlap(this, getWorldPointer()->getActor(i)) && getWorldPointer()->getActor(i)->isDamageable() ) {
            getWorldPointer()->getActor(i)->setHitpoints(getWorldPointer()->getActor(i)->getHitpoints() - 5);
            if (getWorldPointer()->getActor(i)->getHitpoints() <= 0)
                getWorldPointer()->getActor(i)->isAlive(false);
            this->isAlive(false);
            return;
        }
    }
    moveAngle(this->getDirection(), SPRITE_WIDTH);
    setDistTravelled(getDistTravelled() + SPRITE_WIDTH);
    if (getDistTravelled() >= getTravelDistance()){
        isAlive(false);
    }
}
    
// -------------------- NO BASE CLASSES ---------------------------

Dirt::Dirt(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Actor(IID_DIRT, startX, startY, gameWorld, 0, 1, size)
{
    isAlive(true);
    setHitpoints(0);
    isBlock(true);
    isDamageable(true);
}

void Dirt::doSomething(){
    //Hi I'm dirt
    
    
}

Pit::Pit(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Actor(IID_PIT, startX, startY, gameWorld, 0, 1, size)
{
    isDamageable(false);
    isAlive(true);
    setHitpoints(0);
    m_inventorySalm = 5;
    m_inventoryAggSalm = 3;
    m_inventoryEColi = 2;
    gameWorld->setNumBacteria(gameWorld->getNumBacteria() + 1);
}

void Pit::doSomething(){
    
}

// -------------------- BACTERIA BASE CLASSES ---------------------------

Salmonella::Salmonella(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Bacteria(IID_SALMONELLA, startX, startY, gameWorld, 90, 0, size)
{
    setHitpoints(4);
}

AggressiveSalmonella::AggressiveSalmonella(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Bacteria(IID_SALMONELLA, startX, startY, gameWorld, 90, 0, size)
{
    setHitpoints(10);
}

EColi::EColi(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Bacteria(IID_ECOLI, startX, startY, gameWorld, 90, 0, size)
{
    setHitpoints(5); 
}


// -------------------- GOODIE BASE CLASSES ---------------------------

Food::Food(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Goodies(IID_FOOD, startX, startY, gameWorld, 90, 1, size)
{
    setLifetime(10000000);
    isBlock(false);
}
//• Food cannot be damaged by spray or flames.
//• Food does not block the movement of bacteria.
//• Food does not block the movement of spray or flames.


RestoreHealth::RestoreHealth(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Goodies(IID_RESTORE_HEALTH_GOODIE, startX, startY, gameWorld, 0, 1, size)
{
    
}

Flamethrower::Flamethrower(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Goodies(IID_FLAME_THROWER_GOODIE, startX, startY, gameWorld, 0, 1, size)
{
    
}

ExtraLife::ExtraLife(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Goodies(IID_EXTRA_LIFE_GOODIE, startX, startY, gameWorld, 0, 1, size)
{
    
}

Fungus::Fungus(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Goodies(IID_FUNGUS, startX, startY, gameWorld, 0, 1, size)
{
    isDamageable(true);
    setDamage(20);
}


// -------------------- PROJECTILE BASE CLASSES ---------------------------

Flame::Flame(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Projectile(IID_FLAME, startX, startY, gameWorld, dir, 1, size)
{
    isAlive(true);
    setHitpoints(0);
    setTravelDistance(32);
}


Spray::Spray(double startX, double startY, StudentWorld* gameWorld, Direction dir, int depth, double size)
    : Projectile(IID_SPRAY, startX, startY, gameWorld, dir, 1, size)
{
    isAlive(true);
    setHitpoints(0);
    setTravelDistance(112);
}


