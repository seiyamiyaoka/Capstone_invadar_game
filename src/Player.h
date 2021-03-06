#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Missile.h"
#include "Score.h"

class Player
{
  public:
    enum class Direction { kLeft, kRight };
    Player(int grid_width, int grid_height) :
           grid_width(grid_width), grid_height(grid_height), x{static_cast<float>(grid_width / 2)},y{static_cast<float>(grid_height - 1)}, missile{}{}
    void setScore(Score* score);
    void Update();
    void Attack();
    Direction direction = Direction::kLeft;
    int getX();
    int getY();
    float speed{0.1f};
    float x{16.0f};
    float y;
    void dead();
    bool alive{true};
    Missile& getMissile();
    Score* score;
  private:
    int grid_width;
    int grid_height;
    Missile missile;
};

#endif