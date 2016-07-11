#ifndef RANGEDATTACK_H
#define RANGEDATTACK_H
#include <GameObjects/Attacks/attack.h>

class RangedAttack: public Attack{
public:
    RangedAttack(int,int,int,int,int,int);
    virtual void draw(QPainter *);
    virtual void update();
    virtual void inRange(Level *);
    int getSpeed();


private:
    int speed;

};
#endif // RANGEDATTACK_H
