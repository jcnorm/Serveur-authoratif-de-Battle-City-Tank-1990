//#include "appconfig.h"
//#include "app_state/game.h"
#include "objects/tank.h"
//#include "objects/enemy.h"
#include "cheat.h"
#include <algorithm>

double Cheat::increment_speed(double speed){
    return speed + 0.07;
}

unsigned int Cheat::increment_ammo_clip(unsigned int clip_size){
    return ++clip_size;
}

void Cheat::shorten_reload_time(){
    AppConfig::player_reload_time = std::max((AppConfig::player_reload_time - 20u), 20u);
    return;
}

//Attention! Cause des segfaults
void Cheat::raise_bullet_speed(){
    Cheat::cheated_player_bullet_speed = true;
    Cheat::player_bullet_speed_override += 0.02;
    return;
}

Uint32 Cheat::delay_since_cheat_used = 0;

bool Cheat::cheated_player_bullet_speed = false;
double Cheat::player_bullet_speed_override = AppConfig::bullet_default_speed;
//bool Cheat::player_ammo_cheat = false;
//bool Cheat::player_lives_cheat = false;
//bool Cheat::player_shield_cheat = false;
//bool Cheat::player_refire_cheat = false;

//bool Cheat::enemy_speed_cheat = false;
//bool Cheat::enemy_ammo_cheat = false;
//bool Cheat::enemy_lives_cheat = false;
//bool Cheat::enemy_shield_cheat = false;
//bool Cheat::enemy_refire_cheat = false;