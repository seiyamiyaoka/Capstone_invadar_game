#include "Enemy.h"
#include <iostream>
#include <memory>

void Enemy::Update(std::vector<std::unique_ptr<Enemy>> &enemies)
{
  for(const auto &enemy : enemies)
  {
    enemy->y = enemy->y + 1;
    // ミサイルの座標を下向きに更新
    if(enemy->getMissile().isAttack())
    {
      enemy->getMissile().Update(Missile::Direction::down);
    } else {
      enemy->getMissile().doAttack(enemy->x, enemy->y);
    }
  }
}

void Enemy::dead()
{
  alive = false;
}

Missile& Enemy::getMissile()
{
  return missile;
}