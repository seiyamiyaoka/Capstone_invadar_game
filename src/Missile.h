#ifndef MISSILE_H
#define MISSILE_H
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
  private:
    bool attacking{false};
};

#endif
