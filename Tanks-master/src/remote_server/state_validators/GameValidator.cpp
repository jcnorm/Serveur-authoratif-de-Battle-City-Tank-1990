#include "GameValidator.h"

std::string GameValidator::CorrectState(std::vector<std::string> &values) const {
    if(values.size() != 4)
        return "";
    
    std::string correctGamestate = "";
    correctGamestate += current_level.IsValid(std::stoi(values[0])) ? values[0] : std::to_string(current_level.GetMin());
    correctGamestate += "/" + (player_count.IsValid(std::stoi(values[1])) ? values[1] : std::to_string(player_count.GetMin()));
    correctGamestate += "/" + (enemy_to_kill.IsValid(std::stoi(values[2])) ? values[2] : std::to_string(enemy_to_kill.GetMax()));
    correctGamestate += "/" + (enemy_ready_time.IsValid(std::stoi(values[3])) ? values[3] : std::to_string(enemy_ready_time.GetMax()));
    
    return correctGamestate;
}