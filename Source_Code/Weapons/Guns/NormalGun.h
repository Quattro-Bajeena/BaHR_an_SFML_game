#pragma once
#include "Gun.h"

class NormalGun :
	public Gun
{
private:

public:
	NormalGun(std::string name, sf::Texture& texture,
		int clip_size, int capacity, int damage,
		float shoot_time_max, float reload_time_max, float bullet_radius,
		float max_speed, float max_distance, sf::Color bullet_color);
	NormalGun();
	~NormalGun() = default;

	std::vector<Bullet> shootBullet();
};
