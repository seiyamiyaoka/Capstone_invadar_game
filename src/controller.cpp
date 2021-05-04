#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "Player.h"

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
          std::cout << "発射!" << std::endl;
          player.getMissile().doAttack(player.x, player.y);
          break;
      }
      player.Update();
    }
  }
}