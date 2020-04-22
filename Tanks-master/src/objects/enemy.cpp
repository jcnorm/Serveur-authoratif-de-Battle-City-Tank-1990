#include "enemy.h"
#include "../appconfig.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "../Split.h"

Enemy::Enemy()
    : Tank(AppConfig::enemy_starting_point.at(0).x, AppConfig::enemy_starting_point.at(0).y, ST_TANK_A)
{
    direction = D_DOWN;
    m_direction_time = 0;
    m_keep_direction_time = 100;

    m_speed_time = 0;
    m_try_to_go_time = 100;

    m_fire_time = 0;
    m_reload_time = 100;
    lives_count = 1;

    m_bullet_max_size = 1;

    m_frozen_time = 0;

    if(type == ST_TANK_B)
        default_speed = AppConfig::tank_default_speed * 1.3;
    else
        default_speed = AppConfig::tank_default_speed;

    target_position = {-1, -1};

    respawn();
}

Enemy::Enemy(double x, double y, SpriteType type)
    : Tank(x, y, type)
{
    direction = D_DOWN;
    m_direction_time = 0;
    m_keep_direction_time = 100;

    m_speed_time = 0;
    m_try_to_go_time = 100;

    m_fire_time = 0;
    m_reload_time = 100;
    lives_count = 1;

    m_bullet_max_size = 1;

    m_frozen_time = 0;

    if(type == ST_TANK_B)
        default_speed = AppConfig::tank_default_speed * 1.3;
    else
        default_speed = AppConfig::tank_default_speed;

    target_position = {-1, -1};

    respawn();
}

void Enemy::draw()
{
    if(to_erase) return;
    if(AppConfig::show_enemy_target)
    {
        SDL_Color c;
        if(type == ST_TANK_A) c = {250, 0, 0, 250};
        if(type == ST_TANK_B) c = {0, 0, 250, 255};
        if(type == ST_TANK_C) c = {0, 255, 0, 250};
        if(type == ST_TANK_D) c = {250, 0, 255, 250};
        SDL_Rect r = {min(target_position.x, dest_rect.x + dest_rect.w / 2), dest_rect.y + dest_rect.h / 2, abs(target_position.x - (dest_rect.x + dest_rect.w / 2)), 1};
        Engine::getEngine().getRenderer()->drawRect(&r, c,  true);
        r = {target_position.x, min(target_position.y, dest_rect.y + dest_rect.h / 2), 1, abs(target_position.y - (dest_rect.y + dest_rect.h / 2))};
        Engine::getEngine().getRenderer()->drawRect(&r, c, true);
    }
    Tank::draw();
}

void Enemy::update(Uint32 dt)
{
    if(to_erase) return;
    Tank::update(dt);

    if(testFlag(TSF_LIFE))
    {
        if(testFlag(TSF_BONUS))
            src_rect = moveRect(m_sprite->rect, (testFlag(TSF_ON_ICE) ? new_direction : direction) - 4, m_current_frame);
        else
            src_rect = moveRect(m_sprite->rect, (testFlag(TSF_ON_ICE) ? new_direction : direction) + (lives_count -1) * 4, m_current_frame);
    }
    else
        src_rect = moveRect(m_sprite->rect, 0, m_current_frame);

    if(testFlag(TSF_FROZEN)) return;

    m_direction_time += dt;
    m_speed_time += dt;
    m_fire_time += dt;
    if(m_direction_time > m_keep_direction_time)
    {
        m_direction_time = 0;
        m_keep_direction_time = rand() % 800 + 100;

        float p = static_cast<float>(rand()) / RAND_MAX;

        if(p < (type == ST_TANK_A ? 0.8 : 0.5) && target_position.x > 0 && target_position.y > 0)
        {
            int dx = target_position.x - (dest_rect.x + dest_rect.w / 2);
            int dy = target_position.y - (dest_rect.y + dest_rect.h / 2);

            p = static_cast<float>(rand()) / RAND_MAX;

            if(abs(dx) > abs(dy))
                setDirection(p < 0.7 ? (dx < 0 ? D_LEFT : D_RIGHT) : (dy < 0 ? D_UP : D_DOWN));
            else
                setDirection(p < 0.7 ? (dy < 0 ? D_UP : D_DOWN) : (dx < 0 ? D_LEFT : D_RIGHT));
        }
        else
            setDirection(static_cast<Direction>(rand() % 4));
    }
    if(m_speed_time > m_try_to_go_time)
    {
        m_speed_time = 0;
        m_try_to_go_time = rand() % 300;
        speed = default_speed;
    }
    if(m_fire_time > m_reload_time)
    {
        m_fire_time = 0;
        if(type == ST_TANK_D)
        {
            m_reload_time = rand() % 400;
            int dx = target_position.x - (dest_rect.x + dest_rect.w / 2);
            int dy = target_position.y - (dest_rect.y + dest_rect.h / 2);

            if(stop) fire();
            else
                switch (direction)
                {
                case D_UP:
                    if(dy < 0 && abs(dx) < dest_rect.w) fire();
                    break;
                case D_RIGHT:
                    if(dx > 0 && abs(dy) < dest_rect.h) fire();
                    break;
                case D_DOWN:
                    if(dy > 0 && abs(dx) < dest_rect.w) fire();
                    break;
                case D_LEFT:
                    if(dx < 0 && abs(dy) < dest_rect.h) fire();
                    break;
                }
        }
        else if(type == ST_TANK_C)
        {
            m_reload_time = rand() % 800;
            fire();
        }
        else
        {
            m_reload_time = rand() % 1000;
            fire();
        }
    }

    stop = false;
}

void Enemy::destroy()
{
    lives_count--;
//    clearFlag(TSF_BONUS); //możliwe jednokrotne wypadnięcie bonusu
    if(lives_count <= 0)
    {
        lives_count = 0;
        Tank::destroy();
    }
}

unsigned Enemy::scoreForHit()
{
    if(lives_count > 0) return 50;
    return 100;
}

std::string Enemy::State_To_String(){
    const char delimiter = '/';

    return std::string("3") + delimiter + std::to_string(static_cast<int>(pos_x)) +
    delimiter + std::to_string(static_cast<int>(pos_y)) +
    delimiter + std::to_string(default_speed) +
    delimiter + std::to_string(speed) +
    delimiter + std::to_string(static_cast<int>(bullets.size())) +
    delimiter + std::to_string(lives_count) +
    delimiter + std::to_string(m_bullet_max_size) +
    delimiter + std::to_string(m_shield_time) +
    delimiter + std::to_string(m_frozen_time) +
    delimiter + std::to_string(m_reload_time) +
    delimiter + std::to_string(m_fire_time) +
    delimiter + std::to_string(static_cast<int>(type));
}

void Enemy::Apply_State(std::string state){
    auto new_values = Split::split(state,'/');

    if(new_values.size() != 13)
        return;

    pos_x = std::stod(new_values[1]);
    pos_x = std::stod(new_values[2]);
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
    m_reload_time = std::stoi(new_values[10]);
    m_fire_time = std::stoi(new_values[11]);
}
