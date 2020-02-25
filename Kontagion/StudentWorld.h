#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_


#include "GameWorld.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor; //CHECK <-------

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    void addActorToList(Actor* actor);
    Actor* getActor(int i) {return actorList.at(i);}
    double getActorListSize() {return actorList.size();}
    
    void setNumBacteria(int num) {m_numBacteria = num;}
    int getNumBacteria() {return m_numBacteria;}

private:
    std::vector<Actor*> actorList;
    int m_numBacteria;
    
    void addNewObjects();
    void updateStatusText();
};

#endif // STUDENTWORLD_H_


//methods from base class
//unsigned int getLevel() const;
//unsigned int getLives() const;
//void decLives();
//void incLives();
//unsigned int getScore() const;
//void increaseScore(unsigned int howMuch);
//void setGameStatText(string text);
//bool getKey(int& value); 
//void playSound(int soundID);
