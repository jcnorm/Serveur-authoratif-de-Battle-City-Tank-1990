#include "player.h"
#include "../appconfig.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "../cheat.h"
#include <atomic>
#include "../Split.h"

Player::Player()
    : Tank(AppConfig::player_starting_point.at(0).x, AppConfig::player_starting_point.at(0).y, ST_PLAYER_1)
{
    speed = 0;
    lives_count = 11;
    m_bullet_max_size = AppConfig::player_bullet_max_size;
    score = 0;
    star_count = 0;
    m_shield = new Object(0, 0, ST_SHIELD);
    m_shield_time = 0;
    respawn();
}

Player::Player(double x, double y, SpriteType type)
    : Tank(x, y, type)
{
   speed = 0;
   lives_count = 11;
   m_bullet_max_size = AppConfig::player_bullet_max_size;
   score = 0;
   star_count = 0;
   m_shield = new Object(x, y, ST_SHIELD);
   m_shield_time = 0;
   respawn();
}

void Player::update(Uint32 dt)
{
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    Tank::update(dt);
    Cheat::delay_since_cheat_used += dt;

    if(key_state != nullptr && !testFlag(TSF_MENU))
    {
        if(key_state[player_keys.up])
        {
            setDirection(D_UP);
            speed = default_speed;
        }
        else if(key_state[player_keys.down])
        {
            setDirection(D_DOWN);
            speed = default_speed;
        }
        else if(key_state[player_keys.left])
        {
            setDirection(D_LEFT);
            speed = default_speed;
        }
        else if(key_state[player_keys.right])
        {
            setDirection(D_RIGHT);
            speed = default_speed;
        }
        else
        {
            if(!testFlag(TSF_ON_ICE) || m_slip_time == 0)
                speed = 0.0;
        }

        if(key_state[player_keys.fire] && m_fire_time > AppConfig::player_reload_time)
        {
            Bullet* bulletptr = fire();
            if(Cheat::cheated_player_bullet_speed)
                bulletptr->speed = Cheat::player_bullet_speed_override;
            m_fire_time = 0;
        }

        //Cheat inputs
        if(key_state[player_keys.cheat_player_speed] && Cheat::delay_since_cheat_used >= 500){
            Cheat::delay_since_cheat_used = 0;
            default_speed = Cheat::increment_speed(default_speed);
            printf("CHEAT: increased player tank speed to %f \n",default_speed);
        }

        if(key_state[player_keys.cheat_player_ammo] && Cheat::delay_since_cheat_used >= 500){
            Cheat::delay_since_cheat_used = 0;
            m_bullet_max_size = Cheat::increment_ammo_clip(m_bullet_max_size);
            printf("CHEAT: increased player ammo clip to %u \n",m_bullet_max_size);
        }

        if(key_state[player_keys.cheat_player_reload] && Cheat::delay_since_cheat_used >= 500){
            Cheat::delay_since_cheat_used = 0;
            Cheat::shorten_reload_time();
            printf("CHEAT: decreased reload time to %u ms \n", AppConfig::player_reload_time);
        }

        //if(key_state[player_keys.cheat_player_bullet] && Cheat::delay_since_cheat_used >= 500){
        //    Cheat::delay_since_cheat_used = 0;
        //    Cheat::raise_bullet_speed();
        //    printf("CHEAT: increased bullet speed to %f \n", Cheat::player_bullet_speed_override);
        //}
    }

    m_fire_time += dt;

    if(testFlag(TSF_LIFE))
        src_rect = moveRect(m_sprite->rect, (testFlag(TSF_ON_ICE) ? new_direction : direction), m_current_frame + 2 * star_count);
    else
        src_rect = moveRect(m_sprite->rect, 0, m_current_frame + 2 * star_count);

    stop = false;
}

void Player::respawn()
{
    lives_count--;
    if(lives_count <= 0)
    {
        if(bullets.size() == 0) to_erase = true;
        return;
    }

    if(type == ST_PLAYER_1)
    {
        pos_x = AppConfig::player_starting_point.at(0).x;
        pos_y = AppConfig::player_starting_point.at(0).y;
    }
    else
    {
        pos_x = AppConfig::player_starting_point.at(1).x;
        pos_y = AppConfig::player_starting_point.at(1).y;
    }

    dest_rect.x = pos_x;
    dest_rect.y = pos_y;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    setDirection(D_UP);
    Tank::respawn();
    setFlag(TSF_SHIELD);
    m_shield_time = AppConfig::tank_shield_time / 2;
}

void Player::destroy()
{
    if(testFlag(TSF_SHIELD)) return;
    if(testFlag(TSF_BOAT))
    {
        clearFlag(TSF_BOAT);
        return;
    }

    if(star_count == 3)
        changeStarCountBy(-1);
    else
    {
        changeStarCountBy(-3);
        Tank::destroy();
    }
}

Bullet* Player::fire()
{
    Bullet* b = Tank::fire();
    if(b != nullptr)
    {
        if(star_count > 0) b->speed = AppConfig::bullet_default_speed * 1.3;
        if(star_count == 3) b->increased_damage = true;
    }
    return b;
}

void Player::changeStarCountBy(int c)
{
    star_count += c;
    if(star_count > 3) star_count = 3;
    else if(star_count < 0) star_count = 0;

    if(star_count >= 2 && c > 0) m_bullet_max_size++;
    else m_bullet_max_size = 2;

    if(star_count > 0) default_speed = AppConfig::tank_default_speed * 1.3;
    else default_speed = AppConfig::tank_default_speed;
}

std::string Player::State_To_String(){
    const char delimiter = '/';

    return std::string("2") + delimiter + std::to_string(static_cast<int>(pos_x)) +
    delimiter + std::to_string(static_cast<int>(pos_y)) +
    delimiter + std::to_string(default_speed) +
    delimiter + std::to_string(speed) +
    delimiter + std::to_string(static_cast<int>(bullets.size())) +
    delimiter + std::to_string(lives_count) +
    delimiter + std::to_string(m_bullet_max_size) +
    delimiter + std::to_string(m_shield_time) +
    delimiter + std::to_string(m_frozen_time) +
    delimiter + std::to_string(m_fire_time) +
    delimiter + std::to_string(star_count);
}

void Player::Apply_State(std::string state){
    auto new_values = Split::split(state,'/');

    if(new_values.size() != 12)
        return;

    pos_x = std::stod(new_values[1]);
    pos_y = std::stod(new_values[2]);
    default_speed = std::stod(new_values[3]);
    speed = std::stod(new_values[4]);
    int bullet_size = std::stoi(new_values[5]);

    if(bullet_size < static_cast<int>(bullets.size()))
        while(static_cast<int>(bullets.size()) - bullet_size > 0)
            bullets.pop_back();

    lives_count = std::stoi(new_values[6]);
    m_bullet_max_size = std::stoi(new_values[7]);
    m_shield_time = std::stoi(new_values[8]);
    m_frozen_time = std::stoi(new_values[9]);
    m_fire_time = std::stoi(new_values[10]);
    star_count = std::stoi(new_values[11]);
}