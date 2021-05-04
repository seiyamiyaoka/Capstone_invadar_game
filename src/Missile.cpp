#include "Missile.h"

void Missile::Update(Direction direction)
{
  // 敵と味方だと符号を反転させないと異形な
  if(direction == Direction::up)
  {
    y = y + 2;
  } else if (direction == Direction::down)
  {
    y = y + 2;
  }
}

void Missile::doAttack(int xPos, int yPos)
{
  attacking = true;
  x = xPos;
  y = yPos;
}
void Missile::attackCancel()
{
  attacking = false;
}

bool Missile::isAttack()
{
  return attacking;
}