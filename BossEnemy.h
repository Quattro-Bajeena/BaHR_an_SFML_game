#pragma once
#include "Enemy.h"
class BossEnemy :
    public Enemy
{
private:

public:
    BossEnemy(sf::Vector2f position);

    //Functions
    void shoot(sf::Vector2f targetPos);
    void updateAnimations(const float& dt);
};
