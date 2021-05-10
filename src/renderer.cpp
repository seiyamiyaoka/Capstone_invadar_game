#include "renderer.h"
#include "Collision.h"
#include <iostream>
#include <string>
#include <sstream>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width,
                   const std::size_t grid_height)
                   : screen_width(screen_width),
                     screen_height(screen_height),
                     grid_width(grid_width),
                     grid_height(grid_height)
{
  // SDLの初期化
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  // 表示するwindow作成
  sdl_window = SDL_CreateWindow("invadar game",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 screen_width,
                                 screen_height,
                                 SDL_WINDOW_SHOWN
                                 );
  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }
  // renderer作成
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if(nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  // destructorが呼ばれるとwindowを削除
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Player& player, std::vector<std::shared_ptr<Enemy>>& enemies)
{
  // blockを埋める
  // 20 * 20をうめている
  // grid_widhtを5にすると128 * 128をうめて5 * 5になったりする
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // 初期化状態背景をを黒で設定
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  if(!player.alive)
  {
    TTF_Init();
    const char font_path[] = "../src/verdana.ttf";
    TTF_Font *verdanaFont = TTF_OpenFont(font_path, 32);

    if(verdanaFont) {
      SDL_Color textColor = { 255, 255, 255, 255 };
      std::stringstream s;
      s << "result: " << player.score->getScore() << ".Retry press under score!";
      SDL_Surface *textSurface = TTF_RenderText_Solid(verdanaFont, s.str().c_str(), textColor);

      if(textSurface == NULL)
      {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
      } else {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);

        SDL_Rect textRect;
        textRect.x = 30;
        textRect.y = 300;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;
        SDL_RenderCopy(sdl_renderer, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
      }
    }

    TTF_Quit();
  }

  // playerを表示
  block.x = player.x * block.w;
  block.y = player.y * block.h;
  if(player.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  }

  SDL_RenderFillRect(sdl_renderer, &block);

  Checker target_player {
    static_cast<int>(block.x),
    static_cast<int>(block.y - 20),
    static_cast<int>(block.w),
    static_cast<int>(block.h)
  };

  // 敵の表示
  for(const auto& enemy : enemies)
  {
    // block.wをかけないと該当場所に配置されない
    // 単位あたりの数みたいなもの
    // std::cout << enemy.y << std::endl;
    Checker target_enemy {
      static_cast<int>(enemy->x * block.w),
      static_cast<int>(enemy->y),
      static_cast<int>(block.w),
      static_cast<int>(block.h)
    };
    // NOTE: playerが敵に接触したか確認
    Collision collision(target_player, target_enemy);
    if(collision.isCollid())
    {
      std::cout << "HIT=================" << std::endl;
      player.dead();
    }

    // NOTE: 敵が生きているか確認
    if(enemy->alive) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x1A, 0xCC, 0xFF);
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    }
    block.x = enemy->x * block.w;
    block.y = enemy->y;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  for(const auto& enemy : enemies)
  {
    if(enemy->getMissile().isAttack()) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xAA, 0xCC, 0xFF);
      Missile& enemyMissile = enemy->getMissile();
      block.x = enemyMissile.x * block.w;
      block.y = (enemy->y * block.h) - (enemyMissile.y * block.h);
    }
    // 微修正する
    Missile& enemyMissile = enemy->getMissile();
    Checker target_enemy_missile {
      static_cast<int>(block.x),
      static_cast<int>(block.y),
      static_cast<int>(block.w),
      static_cast<int>(block.h)
    };

    Collision collision_enemy_missile_and_player(target_enemy_missile, target_player);
    if(collision_enemy_missile_and_player.isCollid()) {
      player.dead();
    }
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  if(player.getMissile().isAttack())
  {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    Missile& playerMissile = player.getMissile();
    block.x = playerMissile.x * block.w;
    // std::cout << "block height is: " << player.y << std::endl;
    // block.h == 20
    // player.h == 31
    // 620 - 20 = 600
    // 後半のblock.hにあたる部分が可変する
    block.y = (player.y * block.h) - playerMissile.y;

    Checker target_missile {
      static_cast<int>(playerMissile.x * block.w),
      static_cast<int>(block.y),
      static_cast<int>(block.w),
      static_cast<int>(block.h)
    };

    // 敵とミサイルの衝突をチェックしている
    for(const auto& enemy : enemies)
    {
      Checker target_enemy {
        static_cast<int>(enemy->x * block.w),
        static_cast<int>(enemy->y),
        static_cast<int>(block.w),
        static_cast<int>(block.h)
      };
      // 敵とミサイルの衝突をチェックしている
      Collision collision(target_missile, target_enemy);
      if (collision.isCollid() && enemy->alive) {
        enemy->dead();
        player.score->CountScore();
      }
    }
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  // renderを更新
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"game Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
