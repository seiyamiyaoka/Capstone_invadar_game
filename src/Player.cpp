#include "Player.h"
#include <iostream>

Missile& Player::getMissile()
{
  return missile;
}

void Player::Update()
{
  switch(direction) {
    case Direction::kLeft:
      x -= speed;
      break;
    case Direction::kRight:
      x += speed;
      break;
  }
  x = fmod(x + grid_width, grid_width);
}

void Player::dead()
{
  alive = false;
}

void Player::setScore(Score* gameScore)
{
  score = gameScore;
}