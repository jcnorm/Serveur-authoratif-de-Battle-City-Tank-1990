#include "appconfig.h"
#include "app_state/game.h"
#include "objects/player.h"
#include "objects/enemy.h"

class Cheat {

public:
    static bool cheated_player_bullet_speed;
    static double player_bullet_speed_override;
    //static bool player_ammo_cheat;
    //static bool player_lives_cheat;
    //static bool player_shield_cheat;
    //static bool player_refire_cheat;

    //static bool enemy_speed_cheat;
    //static bool enemy_ammo_cheat;
    //static bool enemy_lives_cheat;
    //static bool enemy_shield_cheat;
    //static bool enemy_refire_cheat;

    static Uint32 delay_since_cheat_used;

    static double increment_speed(double speed);

    static unsigned increment_ammo_clip(unsigned clip_size);

    static void shorten_reload_time();

    static void raise_bullet_speed();
};