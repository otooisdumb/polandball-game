#include "playerstatistics.h"

PlayerStatistics::PlayerStatistics(int radius, int speed, int maxhealth, bool ally, std::vector<int> melee, std::vector<int> ranged, std::vector<int> ult, int jumps):
ActorStatistics(radius, speed, maxhealth, ally){
    this->meleeAtk = melee;
    this->jumpCount = jumps;
    this->rangedAtk = ranged;
    this->ultAtk = ult;
}

std::vector<int> PlayerStatistics::getMeleeInfo(){
    return meleeAtk;
}

int PlayerStatistics::getJumpCount(){
    return jumpCount;
}

std::vector<int> PlayerStatistics::getRangedInfo(){
    return rangedAtk;
}

std::vector<int> PlayerStatistics::getUltInfo(){
    return ultAtk;
}
