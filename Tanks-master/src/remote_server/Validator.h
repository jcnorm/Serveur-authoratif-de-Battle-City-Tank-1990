#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <iostream>
#include "Interval.h"
#include "AppconfigValidator.h"

namespace Validator {

    enum ValidationType{
        Appconfig,
        Game,
        Player,
        Enemy
    };

    template<ValidationType Type>
    void Validate() {
        std::cout << "Generic Validation" << std::endl;
    }

    template<>
    void Validate<ValidationType::Appconfig>() {
        Interval test(1,3);
        std::cout << test.IsValid(2) << std::endl;
        std::cout << test.IsValid(1) << std::endl;
        std::cout << test.IsValid(3) << std::endl;
        std::cout << test.IsValid(4) << std::endl;
        std::cout << "Validating Appconfig" << std::endl;
    }

    template<>
    void Validate<ValidationType::Game>() {
        std::cout << "Validating Game" << std::endl;
    }

    template<>
    void Validate<ValidationType::Player>() {
        std::cout << "Validating Player" << std::endl;
    }

    template<>
    void Validate<ValidationType::Enemy>() {
        std::cout << "Validating Enemy" << std::endl;
    }

    void ValidateMessage(std::string message){

        auto type = stoi(message.substr(0, message.find('/')));


        switch(type){
            case ValidationType::Appconfig:
                Validate<ValidationType::Appconfig>();
                break;

            case ValidationType::Game:
                Validate<ValidationType::Game>();
                break;

            case ValidationType::Player:
                Validate<ValidationType::Player>();
                break;

            case ValidationType::Enemy:
                Validate<ValidationType::Enemy>();
                break;

            default:
                std::cout << "Invalid validation type" << std::endl;
                break;
        }
    }
    
}

#endif