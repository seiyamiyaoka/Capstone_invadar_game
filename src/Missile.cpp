#include "Missile.h"
#include "Enemy.h"
#include <iostream>
#include <mutex>
#include <algorithm>

class WaitingEnemies
{
  public:
    WaitingEnemies(){}
    Missile& popBack()
    {
      std::unique_lock<std::mutex>uLock(_mutex);
      _cond.wait(uLock, [this] { return !_enemies.empty() && attack; });
      auto e = _enemies.back();
      Missile& m = e->getMissile();
      m.doAttack(e->x, e->y);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      _enemies.pop_back();
      return m;

    }
    void pushBack(std::shared_ptr<Enemy> e)
    {
      // ロック取得
      std::lock_guard<std::mutex> myLock(_mutex);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      _enemies.emplace_back(e);
      _cond.notify_one();
    }
    bool attack{false};
    int Size()
    {
      return _enemies.size();
    }
  private:
    std::vector<std::shared_ptr<Enemy>> _enemies;
    std::mutex _mutex;
    std::condition_variable _cond;
};

void Missile::Simurate(std::vector<std::shared_ptr<Enemy>> enemies)
{
  std::vector<std::future<void>> futures;
  std::shared_ptr<WaitingEnemies> queue(new WaitingEnemies);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  for(const auto &enemy : enemies)
  {
    futures.emplace_back(std::async(std::launch::async, &WaitingEnemies::pushBack, queue, enemy));
  }

  futures.begin()->wait();

  while(queue->Size() > 0) {
    queue->attack = true;
    queue->popBack();
  }
  Simurate(enemies);
}

void Missile::Update(Direction direction)
{
  const auto PlayerMissileVelocity = 5.5;
  const auto EnemyMissileVelocity = 1;
  if(direction == Direction::up)
  {
    y = y + PlayerMissileVelocity;
  } else if (direction == Direction::down)
  {
    y = y + EnemyMissileVelocity;
  }
}

void Missile::doAttack(int xPos, int yPos)
{
  attacking = true;
  x = xPos;
  y = yPos;
}
void Missile::attackCancel()
{
  attacking = false;
}

bool Missile::isAttack()
{
  return attacking;
}
