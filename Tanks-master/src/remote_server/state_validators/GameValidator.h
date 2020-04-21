#ifndef GAME_VALIDATOR_H
#define GAME_VALIDATOR_H

#include "StateValidator.h"
#include "Interval.h"
#include <limits>

class GameValidator : public StateValidator {
    Interval<int> current_level;      
    Interval<int> player_count;
    Interval<int> enemy_to_kill;      
    Interval<int> enemy_ready_time;     
public:
    GameValidator() : current_level(0,35), player_count(1,2), enemy_to_kill(0,20), enemy_ready_time(0,std::numeric_limits<int>::max()) {}
    std::string CorrectState(std::vector<std::string> &values) const override;
};

#endif