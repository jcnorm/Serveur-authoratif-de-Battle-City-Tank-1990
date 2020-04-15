#ifndef APPCONFIG_VALIDATOR_H
#define APPCONFIG_VALIDATOR_H

#include "StateValidator.h"
#include "Interval.h"

class AppConfigValidator : public StateValidator {
    Interval<int> enemy_start_count;      
    Interval<int> player_bullet_max_size;
    Interval<int> tank_shield_time;      
    Interval<int> tank_frozen_time;     
    Interval<int> protect_eagle_time;   
    Interval<int> player_reload_time;
    Interval<int> enemy_max_count_on_map; 
    Interval<double> tank_default_speed;  
    Interval<double> bullet_default_speed;
public:
    AppConfigValidator() : enemy_start_count(20), player_bullet_max_size(2), tank_shield_time(10000), tank_frozen_time(8000),
        protect_eagle_time(15000), player_reload_time(120), enemy_max_count_on_map(4), tank_default_speed(0.08), bullet_default_speed(0.23) 
    {}
    std::string CorrectState(std::vector<std::string> &values) const override;
};

#endif