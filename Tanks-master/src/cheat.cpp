//#include "appconfig.h"
//#include "app_state/game.h"
#include "objects/tank.h"
//#include "objects/enemy.h"
#include "cheat.h"


bool Cheat::flip_flag(bool flag){
    return !flag;
}

unsigned int Cheat::increment_ammo_clip(unsigned int clip_size){
    return ++clip_size;
}

double Cheat::increment_speed(double speed){
    return speed + 0.07;
}

bool Cheat::player_speed_cheat = false;
bool Cheat::player_ammo_cheat = false;
bool Cheat::player_lives_cheat = false;
bool Cheat::player_shield_cheat = false;
bool Cheat::player_refire_cheat = false;

bool Cheat::enemy_speed_cheat = false;
bool Cheat::enemy_ammo_cheat = false;
bool Cheat::enemy_lives_cheat = false;
bool Cheat::enemy_shield_cheat = false;
bool Cheat::enemy_refire_cheat = false;

Uint32 Cheat::delay_since_cheat_used = 0;