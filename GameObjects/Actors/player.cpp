#include "player.h"
#include <stdio.h>

Player::Player(int x, int y, PlayerStatistics *stat) : Actor(x, y, stat){
    keySet = new QSet<int>();
    this->jumpCount = 0;
    this->verticalSpeed = 0;
    this->stats = stat;
    this->jumpDelayCount = 0;
    this->jumpDelay = 28;
}

Player::~Player(){
}

void Player::addKey(int key){
    (*keySet) += key;
}

void Player::removeKey(int key){
    (*keySet) -= key;
    if(key == Qt::Key_Up){
        this->maximizeJump();
    }
}

void Player::endJump(){
    jumpCount = stats->getMaxJumps();
    verticalSpeed = 0;
}

void Player::update(){
    int x = Qt::Key_Up;
    if(keySet->contains(x)){
        if(jumpDelayCount == jumpDelay){
        this->jump();
        this->updateLocation(0, verticalSpeed);
        }
    }
    if(keySet->contains(Qt::Key_Right)){
        this->updateLocation(stats->getSpeed(), 0);
        setFacing(false);
    }
    if(keySet->contains(Qt::Key_Left)){
        this->updateLocation(-stats->getSpeed(), 0);
        setFacing(true);
    }
}

void Player::jump(){
    if(jumpCount < this->stats->getMaxJumps()){
        jumpCount += 1;
        if(verticalSpeed < 1){
            verticalSpeed = 4;
        }
    }
    else{
        verticalSpeed = 0;
    }
}

void Player::resetJump(){
    jumpCount = 0;
    verticalSpeed = 0;
    if(jumpDelayCount < jumpDelay){
        printf("%d\n",jumpDelayCount);
        jumpDelayCount += 1;
    }
}

void Player::maximizeJump(){
    printf("maximized\n");
    if(jumpCount == 0){
        jumpCount = this->stats->getMaxJumps();
    }
    if(jumpCount == this->stats->getMaxJumps()){
        jumpDelayCount = 0;
    }
}

void Player::draw(QPainter * painter){
    painter->setBrush(Qt::blue);
    painter->drawEllipse(*(getDrawingPosition()), drawingHeight, drawingWidth);
}

MeleeAttack* Player::primaryAttack(){
    AttackStatistics* melle = stats->getMeleeInfo();
    return new MeleeAttack(this->getCenter()->x(),this->getCenter()->y() + melle->getHeight()/2, melle, this);
}

RangedAttack* Player::secondaryAttack(){
    AttackStatistics* melle = stats->getRangedInfo();
    return new RangedAttack(this->getCenter()->x()+this->getRadius(),this->getCenter()->y() + melle->getHeight()/2, melle);
}

Attack* Player::ultAttack(){
    AttackStatistics *ult = stats->getUltInfo();
    Attack* attack;
    if(ult->isMelee()){
        attack = new MeleeAttack(this->getCenter()->x(),this->getCenter()->y() + ult->getHeight()/2, ult, this);
    }
    else{
        attack = new RangedAttack(this->getCenter()->x(),this->getCenter()->y() + ult->getHeight()/2, ult);

    }
    return attack;
}
