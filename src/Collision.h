#ifndef COLLISION_H
#define COLLISION_H


struct Checker {
  int x;
  int y;
  int w;
  int h;
};

class Collision
{
  public:
    Collision(Checker a, Checker b) : checker_a{a}, checker_b{b}{};
    bool isCollid();
  private:
    Checker checker_a;
    Checker checker_b;
};

#endif