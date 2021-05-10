#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <vector>
#include "Missile.h"
#include <memory>

class Enemy
{
  public:
    Enemy(int x, int y) : x(x), y(y), missile{}{}
    static void Update(std::vector<std::shared_ptr<Enemy>> &enemies);
    float x;
    float y;
    bool alive{true};
    void dead();
    SDL_Point point;
    Missile& getMissile();
  private:
    Missile missile;
};

#endif
