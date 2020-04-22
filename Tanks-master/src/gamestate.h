#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>
#include "app_state/appstate.h"

namespace Gamestate{
    [[nodiscard]] std::string To_String(AppState* state);
    void Apply_State(std::string server_response, AppState* state);
};

#endif