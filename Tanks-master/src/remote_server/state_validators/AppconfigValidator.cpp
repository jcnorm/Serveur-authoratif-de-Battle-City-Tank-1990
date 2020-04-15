#include "AppconfigValidator.h"

std::string AppConfigValidator::CorrectState(std::vector<std::string> &values) const {
    if(values.size() != 9)
        return "";
    
    std::string correctGamestate = "";
    correctGamestate += enemy_start_count.IsValid(std::stoi(values[0])) ? values[0] : std::to_string(enemy_start_count.GetMin());
    correctGamestate += "/" + (player_bullet_max_size.IsValid(std::stoi(values[1])) ? values[1] : std::to_string(player_bullet_max_size.GetMin()));
    correctGamestate += "/" + (tank_shield_time.IsValid(std::stoi(values[2])) ? values[2] : std::to_string(tank_shield_time.GetMin()));
    correctGamestate += "/" + (tank_frozen_time.IsValid(std::stoi(values[3])) ? values[3] : std::to_string(tank_frozen_time.GetMin()));
    correctGamestate += "/" + (protect_eagle_time.IsValid(std::stoi(values[4])) ? values[4] : std::to_string(protect_eagle_time.GetMin()));
    correctGamestate += "/" + (player_reload_time.IsValid(std::stoi(values[5])) ? values[5] : std::to_string(player_reload_time.GetMin()));
    correctGamestate += "/" + (enemy_max_count_on_map.IsValid(std::stoi(values[6])) ? values[6] : std::to_string(enemy_max_count_on_map.GetMin()));
    correctGamestate += "/" + (tank_default_speed.IsValid(std::stod(values[7])) ? values[7] : std::to_string(tank_default_speed.GetMin()));
    correctGamestate += "/" + (bullet_default_speed.IsValid(std::stod(values[8])) ? values[8] : std::to_string(bullet_default_speed.GetMin()));
    
    return correctGamestate;
}