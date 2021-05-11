# Simple invador game

<img src="images/playimage.gif"/>

## Dependencies for Running Locally
* cmake >= 3.19.4
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 3.81 (Mac)
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
* gcc/g++ >= 5.4
  * Mac: - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
* SDL2 >= 2.0.14
  * The SDL2 2.0.14 source code can be found [here](https://www.libsdl.org/download-2.0.php)
* SDL2_ttf >= https://www.libsdl.org/projects/SDL_ttf/
  1. download sdl_ttf
  2. Unzip the zip file
  3. ./configure
  4. make
  5. make install

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Capstone`.

## Project description
This is a simple invader game.
The function is
- player can move left and right.
- player can shoot missiles.
- Enemy shoots missiles.
- The score is displayed.

## file tree

```sh
.
├── CMakeLists.txt
├── README.md
├── build
├── include
│   └── defs.h
└── src
    ├── Collision.cpp
    ├── Collision.h
    ├── Enemy.cpp
    ├── Enemy.h
    ├── Missile.cpp
    ├── Missile.h
    ├── Player.cpp
    ├── Player.h
    ├── Score.cpp
    ├── Score.h
    ├── controller.cpp
    ├── controller.h
    ├── game.cpp
    ├── game.h
    ├── main.cpp
    ├── renderer.cpp
    ├── renderer.h
    └── verdana.ttf // font file
```


## class structure

* Game class
  - initializer
  - destructure
  - Run
  - Update
* Controller class
  - HandleInput
  - ChangeDirection
* Renderer
  - initializer
  - destructure
  - Render
  - UpdateWindowTitle
* Player class
  - initializer
  - enum Direction
  - setScore
  - Update
  - Attack
  - getX
  - getY
  - speed
  - x
  - y
  - getMissile
  - score
* Enemy class
  - initializer
  - Update
  - x
  - y
  - dead
  - getMissile
* Missile class
  - enum Direction
  - initializer
  - x
  - y
  - Update
  - doAttack
  - attackCancel
  - isAttack
  - Simurate
  - attackExecute
* Score class
  - initializer
  - destructure
  - CountScore
  - getScore
* Collision class
  - initializer
  - isCollid

## about each rubric point addressed.

### Loops, Functions, I/O
* The project accepts user input and processes the input.
  - controller.cpp:16
  - It receives user input using function provided by the library(SDL_PollEvent and reference event).

### Object Oriented Programming
* Class constructors utilize member initialization lists.
  - Enemy.h:12
  - The coordinates and missiles are set when Enemy is initialized.

### Memory Management
* The project uses smart pointers instead of raw pointers.
  - game.h:22

### Concurrency
* A mutex or lock is used in the project.
  - Missile.cpp:26
  - Since there is a possibility to access _enemies at the same time, we get a lock and limit access.
* A condition variable is used in the project.
  - Missile.cpp:39
  - Missile.cpp:14
  - It is used to launch missiles when there are enemies and they are ready to attack.

