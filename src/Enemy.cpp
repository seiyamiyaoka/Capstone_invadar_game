#include <iostream>
#include <future>
#include <mutex>
#include <algorithm>
#include "Enemy.h"

void Enemy::Update(std::vector<std::shared_ptr<Enemy>> &enemies)
{
  for(const auto &enemy : enemies)
  {
    enemy->y = enemy->y + 0.1;
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