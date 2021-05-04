/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <iostream>
#include "renderer.h"
#include "controller.h"
#include "game.h"

int main(int argc, char* argv[])
{
	// set 60frame
	constexpr std::size_t kFramePersecond{60};
	// 1frame is 16.666
	constexpr std::size_t kMsPerFrame{1000 / kFramePersecond};

	constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};

  // gridの数 640を32分割してくれている
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

	Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
	Controller controller;

	Game game(kGridWidth, kGridHeight);
	game.Run(controller, renderer, kMsPerFrame);
	std::cout << "Game has terminated successfully!\n";
	return 0;
}
