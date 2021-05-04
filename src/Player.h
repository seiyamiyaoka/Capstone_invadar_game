#ifndef PLAYER_H
#define PLAYER_H

#include <SDL_image.h>
#include <SDL.h>
#include <string>
#include "Missile.h"
#include "Score.h"

class Player
{
  public:
    enum class Direction { kLeft, kRight };
    Player(int grid_width, int grid_height) :
           grid_width(grid_width), grid_height(grid_height), x{static_cast<float>(grid_width / 2)},y{static_cast<float>(grid_height - 1)}, missile{}{}
    void setTexture(SDL_Texture* texture);
    Direction direction = Direction::kLeft;
    void Update();
    void Attack();
    SDL_Texture* getTexture();
    float speed{0.1f};
    int getX();
    int getY();
    float x{16.0f};
    float y;
    void dead();
    bool alive{true};
    Missile& getMissile();
    Score* score;
    void setScore(Score* score);
  private:
    SDL_Texture* _texture;
    int grid_width;
    int grid_height;
    Missile missile;
};

#endif