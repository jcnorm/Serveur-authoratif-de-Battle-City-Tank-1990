#include "gamestate.h"
#include "appconfig.h"
#include <vector>
#include "Split.h"

[[nodiscard]] std::string Gamestate::To_String(AppState* state){
    const char delimiter = '|';
    auto appstate_string = state->State_To_String();

    if(appstate_string.size() == 0)
        return AppConfig::State_To_String();

    return AppConfig::State_To_String() + delimiter + appstate_string;
}

void Gamestate::Apply_State(std::string server_response, AppState* state){
    auto sections = Split::split(server_response, '|');

    AppConfig::Apply_State(sections[0]);

    if(sections.size() > 1)
         state->Apply_State(std::vector<std::string>(sections.cbegin() + 1, sections.cend()));
}