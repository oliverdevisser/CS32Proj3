#ifndef ACTOR_H_
#define ACTOR_H_

#include "StudentWorld.h"
#include "GraphObject.h"
#include <vector>


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
    
public:
    Actor(int ImageID, double startX, double startY, StudentWorld* worldPointer = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
    virtual void doSomething() = 0; //virtual doSomething function
    
    bool overlap(Actor* a1, Actor* a2){
        if (a1 == a2)
            return false;
        double dist = sqrt(((a1->getX() - a2->getX()) * (a1->getX() - a2->getX())) + ((a1->getY() - a2->getY()) * (a1->getY() - a2->getY())));
        return (dist < SPRITE_WIDTH);
    }
    
    void isAlive(bool alive){
        m_isAlive = alive;
    }
    
    bool isAlive(){
        return m_isAlive;
    }
    
    void setHitpoints(int hp){
        m_hitpoints = hp;
    }
    
    int getHitpoints(){
        return m_hitpoints;
    }
    
    StudentWorld* getWorldPointer(){
        return m_worldPointer;
    }
    
    int getLifetime() {
        return m_lifetime;
    }
    
    void setLifetime(int time) {
        m_lifetime = time;
    }
    
    int getDamage() {
        return m_damage;
    }
    
    void setDamage(int damage) {
        m_damage = damage;
    }
    
    bool isBlock() {
        return m_block;
    }
    
    void isBlock(bool block){
        m_block = block;
    }
    
    bool isDamageable() {
        return m_damageable;
    }
    
    void isDamageable(bool damageable){
        m_damageable = damageable;
    }
    
    int getSprays() {return m_sprays;} //so that anything can access these methods from a list of actors
    void setSprays(int sprays) {m_sprays = sprays;}
    int getFlames() {return m_flames;}
    void setFlames(int flames) {m_flames = flames;}
    
private:
    bool m_isAlive;
    int m_hitpoints;
    StudentWorld* m_worldPointer;
    int m_lifetime;
    int m_damage;
    bool m_block;
    int m_sprays;
    int m_flames;
    bool m_damageable;
};

// -------------------- ACTOR BASE CLASSES ---------------------------

class Socrates : public Actor {
    
public:
    Socrates(double startX, double startY, StudentWorld* gameWorld, Direction dir = 0, int depth = 0, double size = 1.0);
    void doSomething();
    void moveSocrates(int dir);
   
private:
    StudentWorld* m_studentWorld;
    
};

class Bacteria : public Actor {
    
public:
    Bacteria(int ImageID, double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
    void doSomething();
    int getPlanDist(){return m_planDist;}
    void setPlanDist(int planDist){m_planDist = planDist;}
    
    bool movementOverlap(Actor* a1, double targetX, double targetY){
        double dist = sqrt(((a1->getX() - targetX) * (a1->getX() - targetX)) + ((a1->getY() - targetY) * (a1->getY() - targetY)));
        return (dist < (SPRITE_WIDTH/2));
    }
    
private:
    int m_planDist;
    
};

class Goodies : public Actor {
    
public:
    Goodies(int ImageID, double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
    void doSomething();
    
private:
    
};

class Projectile : public Actor {
    
public:
    Projectile(int ImageID, double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
    void doSomething();
    void setTravelDistance(int dist) {m_travelDistance = dist;}
    int getTravelDistance() {return m_travelDistance;}
    void setDistTravelled(int dist) {m_distTravelled = dist;}
    int getDistTravelled() {return m_distTravelled;}
private:
    int m_travelDistance;
    int m_distTravelled;
};

// -------------------- NO BASE CLASS ---------------------------

class Dirt : public Actor {
    
public:
    Dirt(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
    void doSomething();
private:
    
};

class Pit : public Actor {
    
public:
    Pit(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
    void doSomething();
private:
    int m_inventorySalm;
    int m_inventoryAggSalm;
    int m_inventoryEColi;
};

// -------------------- BACTERIA BASE CLASSES ---------------------------

class Salmonella : public Bacteria {
    
public:
    Salmonella(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

class AggressiveSalmonella : public Bacteria {
    
public:
    AggressiveSalmonella(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

class EColi : public Bacteria {
    
public:
    EColi(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

// -------------------- GOODIE BASE CLASSES ---------------------------

class Food : public Goodies {
    
public:
    Food(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

class RestoreHealth : public Goodies {
    
public:
    RestoreHealth(double startX, double startY, StudentWorld* gameWorld, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

class Flamethrower : public Goodies {
    
public:
    Flamethrower(double startX, double startY, StudentWorld* gameWorld, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

class ExtraLife : public Goodies {
    
public:
    ExtraLife(double startX, double startY, StudentWorld* gameWorld, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

class Fungus : public Goodies {
    
public:
    Fungus(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
private:
    
};

// -------------------- PROJECTILE BASE CLASSES ---------------------------

class Flame : public Projectile {
    
public:
    Flame(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
private:

};

class Spray : public Projectile {
    public:
        Spray(double startX, double startY, StudentWorld* gameWorld = nullptr, Direction dir = 0, int depth = 0, double size = 1.0);
    private:

};

#endif // ACTOR_H_


/*

GraphObject(int imageID, double startX, double startY,
int startDirection = 0, int depth = 0);
double getX() const; // in pixels (0-255)
double getY() const; // in pixels (0-255)
void moveTo(double x, double y); // in pixels (0-255)
23
// moveAngle() moves the actor the specified number of units in the
// specified direction.
void moveAngle(Direction angle, int units = 1);
// getPositionInThisDirection() returns a new (x, y) location in the
// specified direction and distance, based on the passed-in angle and the
// GraphObject’s current (x, y) location.
void getPositionInThisDirection(Direction angle, int units,
 double &dx, double &dy);
int getDirection() const; // in degrees (0-359)
void setDirection(Direction d); // in degrees (0-359)
 
 */
