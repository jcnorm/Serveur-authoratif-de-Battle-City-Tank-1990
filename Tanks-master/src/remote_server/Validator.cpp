#include "Validator.h"
#include <iostream>
#include <sstream>
#include <iterator>

namespace Split{
    template <typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delim)) {
            *result++ = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }
}

std::string Validator::ValidateMessage(std::string message){
    auto sections = Split::split(message, section_delimiter); 

    std::string correctedGamestate = "";

    for(int index=0; index<sections.size(); index++){
        auto valueVector = Split::split(sections[index], value_delimiter);
        int type = std::stoi(valueVector[0]);
        auto values = std::vector<std::string>(valueVector.cbegin() + 1, valueVector.cend());

        switch(type){
            case Validator::ValidationType::Appconfig:
                correctedGamestate += std::to_string(type) + value_delimiter + appconfig_V.CorrectState(values);
                break;

            case Validator::ValidationType::Game:
                correctedGamestate += std::to_string(type) + value_delimiter + game_V.CorrectState(values);
                break;

            case Validator::ValidationType::Player:
                correctedGamestate += std::to_string(type) + value_delimiter + player_V.CorrectState(values);
                break;

            case Validator::ValidationType::Enemy:
                correctedGamestate += std::to_string(type) + value_delimiter + enemy_V.CorrectState(values);
                break;
        }

        if(index != sections.size() - 1)
            correctedGamestate += '|';
    }

    return correctedGamestate;
}

