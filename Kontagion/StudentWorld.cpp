#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_numBacteria = 0;
}

StudentWorld::~StudentWorld(){
    cleanUp();
}

int StudentWorld::init()
{
    actorList.push_back(new Socrates(0, VIEW_HEIGHT/2, this)); //Socrates
    int rand = 0;
    int rand2 = 0;
    int num = max(180 - (20 * getLevel()), 20);
    for (int i = 0; i < num; i++){ //dirt first as you don't have to check for overlap
        rand = randInt(-120, 120);
        rand2 = randInt(-sqrt(120*120 - rand*rand), sqrt(120*120 - rand*rand));
        actorList.push_back(new Dirt(VIEW_WIDTH/2 + rand, VIEW_HEIGHT/2 + rand2, this));
    }
    num = getLevel();
    for (int i = 0; i < num; i++){ //pits second
        while (true){
            rand = randInt(-120, 120);
            rand2 = randInt(-sqrt(120*120 - rand*rand), sqrt(120*120 - rand*rand));
            Pit* toAdd = new Pit(VIEW_WIDTH/2 + rand, VIEW_HEIGHT/2 + rand2, this);
            bool isOverlap = false;
            for (int i = 0; i < actorList.size(); i++)
                if (toAdd->overlap(toAdd, actorList.at(i)))
                    isOverlap = true;
            if (isOverlap){
                delete toAdd;
                continue;
            }
            actorList.push_back(toAdd);
            break;
        }
    }
    num = min(5 * getLevel(), 25);
    for (int i = 0; i < num; i++){ //food last
        while (true){
            rand = randInt(-120, 120);
            rand2 = randInt(-sqrt(120*120 - rand*rand), sqrt(120*120 - rand*rand));
            Food* toAdd = new Food(VIEW_WIDTH/2 + rand, VIEW_HEIGHT/2 + rand2, this);
            bool isOverlap = false;
            for (int i = 0; i < actorList.size(); i++)
                if (toAdd->overlap(toAdd, actorList.at(i)))
                    isOverlap = true;
            if (isOverlap){
                delete toAdd;
                continue;
            }
            actorList.push_back(toAdd);
            break;
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::addNewObjects(){
    int rand = randInt(0, 360);
    int chance = randInt(0, max(510 - getLevel() * 10, 200));
    if (chance == 0){
        actorList.push_back(new Fungus(VIEW_WIDTH/2 + VIEW_RADIUS * cos(rand), VIEW_HEIGHT/2 + VIEW_RADIUS * sin(rand), this));
    }
    chance = randInt(0, max(510 - getLevel() * 10, 250));
    int num = randInt(1, 10); //for which goodie
    if (chance == 0){
        if (num <= 6)
            actorList.push_back(new RestoreHealth(VIEW_WIDTH/2 + VIEW_RADIUS * cos(rand), VIEW_HEIGHT/2 + VIEW_RADIUS * sin(rand), this));
        else if (num == 10)
            actorList.push_back(new ExtraLife(VIEW_WIDTH/2 + VIEW_RADIUS * cos(rand), VIEW_HEIGHT/2 + VIEW_RADIUS * sin(rand), this));
        else
            actorList.push_back(new Flamethrower(VIEW_WIDTH/2 + VIEW_RADIUS * cos(rand), VIEW_HEIGHT/2 + VIEW_RADIUS * sin(rand), this));
    }
}

int StudentWorld::move()
{
    if (actorList.at(0)->getHitpoints() <= 0){
        return GWSTATUS_PLAYER_DIED;
    }
    for (int i = 0; i < actorList.size(); i++){ //for some reason when dir is 15 for spray, its always not alive
        
        if (actorList.at(i)->isAlive() == false){
            
            for (int j = i; j < actorList.size() - 1; j++){
                Actor* temp = actorList.at(j);
                actorList.at(j) = actorList.at(j + 1);
                actorList.at(j + 1) = temp;
            }
            delete actorList.at(actorList.size() - 1);
            actorList.pop_back();
            continue;
        }
        
        actorList.at(i)->doSomething();
    }
    if (m_numBacteria <= 0){ //PITS count as bacteria to make this work, make sure decrement numBacteria when pits and bacteria are killed
        return GWSTATUS_FINISHED_LEVEL;
    }
        //Add new objects
    addNewObjects();
        //Update status text
    string statText = "Score: " + to_string(getScore()) + "  Level: " + to_string(getLevel()) + "  Lives: " + to_string(getLives()) + "  Health: " + to_string(actorList.at(0)->getHitpoints()) + "  Sprays: " + to_string(actorList.at(0)->getSprays()) + "  Flames: " + to_string(actorList.at(0)->getFlames());
    setGameStatText(statText);
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i < actorList.size(); i++)
        if (actorList.at(i) != nullptr)
            delete actorList.at(i);
    while (actorList.size() != 0)
        actorList.pop_back();
}

void StudentWorld::addActorToList(Actor* actor){
    actorList.push_back(actor);
    return;
}
