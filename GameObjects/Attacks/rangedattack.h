#ifndef RANGEDATTACK_H
#define RANGEDATTACK_H
#include "GameObjects/Attacks/attack.h"

class RangedAttack: public Attack{
public:
    RangedAttack(int,int, bool, AttackStatistics*);
    virtual void draw(QPainter *);
    virtual void update();
    int getSpeed();


private:
    int speed;

};
#endif // RANGEDATTACK_H
