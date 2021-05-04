#include "Score.h"

void Score::CountScore()
{
  _point += 1;
}

int Score::getScore()
{
  return _point;
}