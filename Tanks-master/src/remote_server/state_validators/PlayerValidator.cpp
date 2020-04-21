#include "PlayerValidator.h"
#include "Interval.h"

std::string PlayerValidator::CorrectState(std::vector<std::string> &values) const {
    if(values.size() != 11)
        return "";

    auto val0 = std::stoi(values[0]);
    auto val1 = std::stoi(values[1]);
    auto val2 = std::stod(values[2]);
    auto val3 = std::stod(values[3]);
    auto val4 = std::stoi(values[4]);
    auto val5 = std::stoi(values[5]);
    auto val6 = std::stoi(values[6]);
    auto val7 = std::stoi(values[7]);
    auto val8 = std::stoi(values[8]);
    auto val9 = std::stoi(values[9]);
    auto val10 = std::stoi(values[10]);
    
    std::string correctGamestate = "";
    correctGamestate += pos_x.IsValid(val0) ? values[0] : std::to_string(pos_x.GetClosestValue(val0));
    correctGamestate += "/" + (pos_y.IsValid(val1) ? values[1] : std::to_string(pos_y.GetClosestValue(val1)));
    correctGamestate += "/" + (default_speed.IsValid(val2) ? values[2] : std::to_string(default_speed.GetClosestValue(val2)));
    correctGamestate += "/" + (speed.IsValid(val3) ? values[3] : std::to_string(speed.GetClosestValue(val3)));
    correctGamestate += "/" + (bullet_count.IsValid(val4) ? values[4] : std::to_string(bullet_count.GetClosestValue(val4)));
    correctGamestate += "/" + (lives_count.IsValid(val5) ? values[5] : std::to_string(lives_count.GetClosestValue(val5)));
    correctGamestate += "/" + (bullet_max_size.IsValid(val6) ? values[6] : std::to_string(bullet_max_size.GetClosestValue(val6)));
    correctGamestate += "/" + (shield_time.IsValid(val7) ? values[7] : std::to_string(shield_time.GetClosestValue(val7)));
    correctGamestate += "/" + (frozen_time.IsValid(val8) ? values[8] : std::to_string(frozen_time.GetClosestValue(val8)));
    correctGamestate += "/" + (fire_time.IsValid(val9) ? values[9] : std::to_string(fire_time.GetClosestValue(val9)));
    correctGamestate += "/" + (star_count.IsValid(val10) ? values[10] : std::to_string(star_count.GetClosestValue(val10)));
    
    return correctGamestate;
}