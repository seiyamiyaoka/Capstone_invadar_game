#include <iostream>
#include "game.h"
#include "Score.h"
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_heigt) : player(new Player(grid_width, grid_heigt)) {
  for(auto i = 0; i < grid_width / 2; i++)
  {
    enemies.emplace_back(std::make_unique<Enemy>(i*2, 2));
  }
}
Game::~Game()
{
  std::cout << "削除" << std::endl;
}

void Game::Update()
{
  if(player->getMissile().isAttack())
  {
    player->getMissile().Update(Missile::Direction::up);
  }
  Enemy::Update(enemies);
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;

  Score* gameScore = new Score();

  int frame_count = 0;
  bool running = true;
  std::thread t1 = std::thread(&Missile::Simurate, enemies);

  player->setScore(gameScore);
  while(running)
  {
    frame_start = SDL_GetTicks();
    // playerは入力によりupdateされる
    controller.HandleInput(running, *player);
    renderer.Render(*player, enemies);

    Update();

    frame_end = SDL_GetTicks();

    frame_count++;
    frame_duration = frame_end - frame_start;

    if(frame_end - title_timestamp >= 1000)
    {
      // 点数を取得して渡す
      renderer.UpdateWindowTitle(player->score->getScore(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
      // if(!player->alive)
      //   running = false;
    }
    if(frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}
