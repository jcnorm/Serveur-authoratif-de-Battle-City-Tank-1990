#include "gamestate.h"

Gamestate::Gamestate() = default;

Gamestate::~Gamestate() = default;

Gamestate::Gamestate(std::string stateString) : message(stateString) {}

Gamestate::Gamestate(const Gamestate& state) : message(state.ToString()) {}

Gamestate& Gamestate::operator=(const Gamestate& state){ message = state.ToString(); }

[[nodiscard]] std::string Gamestate::ToString() const{
    return "2/20/2/10000/8000/15000/120/4/0.08/0.23";
}