#include "stdafx.h"
#include "NormalGun.h"

NormalGun::NormalGun(std::string name, sf::Texture& texture,
    int clip_size, int capacity, int damage,
    float shoot_time_max, float reload_time_max, float bullet_radius,
    float max_speed, float max_distance,
    sf::Color bullet_color)
    :Gun(name,texture,
        clip_size, capacity, damage,
        shoot_time_max, reload_time_max, bullet_radius, max_speed, max_distance,
        bullet_color)
{
}

NormalGun::NormalGun()
    :Gun()
{
    this->name = "NORMAL_GUN";
    this->model = gunModels::NORMAL;
    this->sprite.setTexture(Assets::Get().textures.at("NORMAL_GUN"));
    this->defaultBounds = this->sprite.getGlobalBounds();
    this->magazine = std::make_unique< Magazine>(16, 1000, 0, 0, false);
    this->damage = 6;
    this->shootTimerMax = 0.2f;
    this->reloadTimeMax = 0.5f;
    this->bulletRadius = 15.f;
    this->maxSpeed = 1000.f;
    this->maxDistance = 2000.f;
    this->bulletColor = sf::Color::White;
    this->gunDistance = 30.f;

    
}

std::vector<Bullet> NormalGun::shootBullet()
{
    if (this->shootTimer >= this->shootTimerMax  && this->reloading == false && this->magazine->isEmpty() == false) {
        this->magazine->shoot(1);
        this->shootTimer = 0.f;
        return std::vector<Bullet>{
            Bullet(
                this->gunTip, this->direction,
                this->bulletColor, this->damage* this->damageModifier,
                this->bulletRadius, this->maxSpeed, this->maxDistance
                )};
        
    }
    else return std::vector<Bullet>();
}