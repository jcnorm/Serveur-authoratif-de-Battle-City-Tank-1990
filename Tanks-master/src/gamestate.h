#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>

class Gamestate{
    std::string message;

public:
    Gamestate();
    ~Gamestate();
    Gamestate(std::string stateString);
    Gamestate(const Gamestate& state);
    Gamestate& operator=(const Gamestate& state);

    [[nodiscard]] std::string ToString() const ;
};

#endif