#include "gamestate.h"

Gamestate::Gamestate() = default;

Gamestate::~Gamestate() = default;

Gamestate::Gamestate(std::string stateString) : message(stateString) {}

Gamestate::Gamestate(const Gamestate& state) : message(state.ToString()) {}

Gamestate& Gamestate::operator=(const Gamestate& state){ message = state.ToString(); }

[[nodiscard]] std::string Gamestate::ToString() const{
    std::string appconfigString_V = "0/20/2/10000/8000/15000/120/4/0.08/0.23";
    std::string appconfigString_I = "0/-1/-1/-1/-1/-1/-1/-1/0/0";
    std::string gameString_V = "1/10/1/15/400";
    std::string gameString_I = "1/38/3/25/-1";
    std::string player_V = "2/180/180/0.08/0.104/4/8/2/5000/4000/60/2";
    std::string player_I = "2/-3/389/0.04/1/15/50/200/20000/12000/-1/8";
    std::string enemy_V = "3/180/180/0.08/0.104/4/8/2/5000/4000/500/60/2";
    std::string enemy_I = "3/-3/389/0.04/1/15/50/200/20000/12000/500/-1/3";
    const char delimiter = '|';

    return appconfigString_I + delimiter 
        + gameString_I + delimiter
        + player_V + delimiter + player_I + delimiter 
        + enemy_V + delimiter + enemy_I + delimiter + enemy_V + delimiter + enemy_I + delimiter 
        + enemy_V + delimiter + enemy_I + delimiter + enemy_V + delimiter + enemy_I;
}