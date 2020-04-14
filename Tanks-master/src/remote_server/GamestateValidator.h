#ifndef GAMESTATE_VALIDATOR_H
#define GAMESTATE_VALIDATOR_H

#include <string>

class GamestateValidator{
public:
    virtual std::string CorrectGamestate(std::string receivedState) const = 0;
};

#endif