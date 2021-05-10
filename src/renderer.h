#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Enemy.h"

class Missile;
class Renderer
{
  public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();
    void Render(Player& player, std::vector<std::shared_ptr<Enemy>>& enemies);
    void FinishRender();
    void UpdateWindowTitle(int score, int fps);
    bool loadMedia();
  private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    SDL_Surface *finishPage = NULL;
    SDL_Surface *messageSurface = NULL;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif