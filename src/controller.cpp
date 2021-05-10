#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::ChangeDirection(Player &player,
                         Player::Direction input,
                         Player::Direction opposite) const
{
  player.direction = input;
}

void Controller::HandleInput(bool &running, Player &player) const
{
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {
      // 参照を変更している
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym)
      {
        case SDLK_LEFT:
          ChangeDirection(player, Player::Direction::kLeft, Player::Direction::kRight);
          break;
        case SDLK_RIGHT:
          ChangeDirection(player, Player::Direction::kRight, Player::Direction::kLeft);
          break;
        case SDLK_SEMICOLON:
          if(player.alive) {
            std::cout << "発射!" << std::endl;
            player.getMissile().doAttack(player.x, player.y);
          }
          break;
        case SDLK_UNDERSCORE:
          // wakeup player
          running = true;
          player.alive = true;
          break;
      }
      player.Update();
    }
  }
}