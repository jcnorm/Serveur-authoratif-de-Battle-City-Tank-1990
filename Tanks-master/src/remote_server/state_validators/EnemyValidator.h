#ifndef ENEMY_VALIDATOR_H
#define ENEMY_VALIDATOR_H

#include "StateValidator.h"
#include "Interval.h"
#include <limits>

class EnemyValidator : public StateValidator {
    Interval<int> pos_x;      
    Interval<int> pos_y;
    Interval<double> default_speed;      
    Interval<double> speed;     
    Interval<int> bullet_count;   
    Interval<int> lives_count;
    Interval<int> bullet_max_size; 
    Interval<int> shield_time;  
    Interval<int> frozen_time;
    Interval<int> fire_time;  
    Interval<int> type;
public:
    EnemyValidator() : pos_x(-2,386), pos_y(-2,386), default_speed(0.08, 0.08*1.3), speed(0, 1.3*0.08), bullet_count(0,5),
        lives_count(0,1), bullet_max_size(0,5), shield_time(0,10000), frozen_time(0,8000), fire_time(0,std::numeric_limits<int>::max()), type(0,3)
    {}
    std::string CorrectState(std::vector<std::string> &values) const override;
};

#endif