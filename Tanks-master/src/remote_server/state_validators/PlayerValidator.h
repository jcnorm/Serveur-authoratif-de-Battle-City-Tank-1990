#ifndef PLAYER_VALIDATOR_H
#define PLAYER_VALIDATOR_H

#include "StateValidator.h"
#include "Interval.h"
#include <limits>

class PlayerValidator : public StateValidator {
    Interval<int> pos_x;      
    Interval<int> pos_y;
    Interval<double> default_speed;      
    Interval<double> speed;     
    Interval<int> bullet_count;   
    Interval<int> lives_count;
    Interval<int> bullet_max_size; 
    Interval<int> shield_time;  
    Interval<int> frozen_time;
    Interval<int> star_count; 
    Interval<int> fire_time;  
public:
    PlayerValidator() : pos_x(-500,500), pos_y(-500,500), default_speed(0.08, 0.08*1.3), speed(0, 1.3*0.08), bullet_count(0,5),
        lives_count(0,11), bullet_max_size(0,5), shield_time(0,10000), frozen_time(0,8000), star_count(0,3), fire_time(0,std::numeric_limits<int>::max())
    {}
    std::string CorrectState(std::vector<std::string> &values) const override;
};

#endif