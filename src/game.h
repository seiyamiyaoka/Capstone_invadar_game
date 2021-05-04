#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
  public:
    Game(std::size_t grid_width, std::size_t grid_height
    );
    void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
    void Update();
  private:
    Player player;
    std::vector<Enemy> enemies;
};

#endif