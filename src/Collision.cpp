#include "Collision.h"

bool Collision::isCollid()
{
  int leftA = checker_a.x;
  int rightA = checker_a.x + checker_a.w;
  int topA = checker_a.y;
  int bottomA = checker_a.y + checker_a.h;

  int leftB = checker_b.x;
  int rightB = checker_b.x + checker_b.w;
  int topB = checker_b.y;
  int bottomB = checker_b.y + checker_b.h;

  if( bottomA <= topB )
  {
      return false;
  }

  if( topA >= bottomB )
  {
      return false;
  }

  if( rightA <= leftB )
  {
      return false;
  }

  if( leftA >= rightB )
  {
      return false;
  }
  return true;
}
