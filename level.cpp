#include "level.h"
#include "GameObjects/gameobject.h"
#include "GameObjects/Actors/actor.h"
#include "GameObjects/Platforms/platform.h"
#include "GameObjects/Actors/player.h"
#include <vector>
#include <math.h>

Level::Level(Player * player)
{
    this->player = player;
    tree= KDTree<GameObject*> ();
    tree.insert(player);
    this->gravity = -1;
}

Level::Level(Player * player, std::vector<GameObject *> levelObs, int grav){
    gravity = grav;
    //allObjs = KDTree();
    for(int i = 0; i < levelObs.size(); i++){
        tree.insert(levelObs[i]);
    }
    tree.insert(player);
    this->player = player;
}

Level::~Level(){
}

KDTree<GameObject*> * Level::getObjects(){
    return &tree;
}

void Level::update(){
    /*DO:
     * Update all actors
     * Apply gravity
     */
    int size = tree.size();
    for(int i = 0; i < tree.size(); i++){
        GameObject * obj = tree.get(i);
        obj->update();
    }
    tree.rebuildTree();
    this->checkCollisions();
}

void Level::handlePress(int key){
    player->addKey(key);
    if(player->canAttack()){
        if(key == Qt::Key_Z){
            TempGameObject * attack = player->primaryAttack();
            attack->registerObserver(this);
            tree.insert(attack);
        }
        if(key == Qt::Key_X){
            TempGameObject *attack = player->secondaryAttack();
            attack->registerObserver(this);
            tree.insert(attack);
        }
    }
}

void Level::onDelete(DeleteSubject * willDelete){
    TempGameObject* toDelete = (TempGameObject*)willDelete;
    tree.remove(toDelete);
}

void Level::handleRelease(int key){
    player->removeKey(key);
}


void Level::checkCollisions(){
    std::vector<GameObject*> objs = tree.getElems();
    for(int i = 0; i < objs.size(); i++){
        int objsSize = objs.size();
        GameObject * obj = objs[i];
        int radius = obj->getCollRadius();
        int innerSize = tree.size();
        std::vector<GameObject *> list = tree.rangeSearch(obj, obj->x() - radius, obj->y() + radius,
                                                          obj->x() + obj->getWidth()+ radius, obj->y() -obj->getHeight() - radius);
        for(int a = 0; a < list.size(); a++){
            obj->handleCollision(list[a]);
        }
    }
}
