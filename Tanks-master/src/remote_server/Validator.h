#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <vector>
#include "state_validators/AppconfigValidator.h"
#include "state_validators/GameValidator.h"

class Validator {
    const char section_delimiter = '|';
    const char value_delimiter = '/';
    AppConfigValidator appconfig_V;
    GameValidator game_V;

public:
    Validator() : appconfig_V(), game_V() {}
    ~Validator() = default;

    std::string ValidateMessage(std::string message);

    enum ValidationType{
        Appconfig,
        Game,
        Player,
        Enemy
    };
};

#endif