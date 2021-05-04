#ifndef RENDERER_H
#define RENDERER_H

#include "Player.h"
#include "Enemy.h"
#include "SDL.h"
#include <vector>

class Missile;
class Renderer
{
  public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();
    void Render(Player& player, std::vector<std::unique_ptr<Enemy>>& enemies);
    void FinishRender();
    void UpdateWindowTitle(int score, int fps);
    bool loadMedia();
  private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    SDL_Surface *finishPage = NULL;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif