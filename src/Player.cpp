#include "Player.h"
#include <iostream>

void Player::setTexture(SDL_Texture* texture)
{
  _texture = texture;
}

SDL_Texture* Player::getTexture()
{
  return _texture;
}

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