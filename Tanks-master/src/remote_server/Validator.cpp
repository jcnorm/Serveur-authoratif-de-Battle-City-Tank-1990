#include "Validator.h"
#include <iostream>
#include "Split.h"

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
                break;

            case Validator::ValidationType::Enemy:
                break;
        }

        if(index != sections.size() - 1)
            correctedGamestate += '|';
    }

    std::cout << correctedGamestate << std::endl;

    return correctedGamestate;
}