#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include <vector>
#include "Missile.h"
#include <memory>

class Enemy
{
  public:
    Enemy(int x, int y) : x(x), y(y), missile{}{}
    float x;
    float y;
    static void Update(std::vector<std::shared_ptr<Enemy>> &enemies);
    void dead();
    SDL_Point point;
    bool alive{true};
    Missile& getMissile();
  private:
    Missile missile;
};

#endif
