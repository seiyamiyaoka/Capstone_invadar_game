#ifndef MISSILE_H
#define MISSILE_H

#include <vector>
#include <future>
#include <memory>
class Enemy;
class Missile
{
  public:
    enum class Direction { up, down };
    Missile(int y = 32) : y(y){}
    float x;
    float y{32};
    void Update(Direction direction);
    void doAttack(int xPos, int yPos);
    void attackCancel();
    bool isAttack();
    static void Simurate(std::vector<std::shared_ptr<Enemy>> enemies);
    static void attackExecute(std::vector<std::future<void>> futures);
  private:
    bool attacking{false};
};

#endif
