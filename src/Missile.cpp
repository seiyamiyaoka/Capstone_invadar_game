#include "Missile.h"
#include "Enemy.h"
#include <iostream>
#include <memory>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>


class WaitingMissile
{
  public:
    WaitingMissile(){}
    Missile& popBack()
    {
      std::unique_lock<std::mutex>uLock(_mutex);
      _cond.wait(uLock, [this] { return !_enemies.empty() && attack; });
      auto e = _enemies.back();
      Missile& m = e->getMissile();
      // m.Update(Missile::Direction::down);
      m.doAttack(e->x, e->y);
      std::cout << "更新しています" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "missile y: "<< m.y << "y: " << e->y << std::endl;
      _enemies.pop_back();
      return m;

    }
    void pushBack(std::shared_ptr<Enemy> e)
    {
      // ロック取得
      std::lock_guard<std::mutex> myLock(_mutex);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      _enemies.emplace_back(e);
      std::cout << "pushされています" << std::endl;
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
  // std::vector<std::unique_ptr<Enemy>> &enemies
  std::vector<std::future<void>> futures;
  // std::vector<std::future<void>> futures;
  std::shared_ptr<WaitingMissile> queue(new WaitingMissile);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "simurateがよばれるよ" << std::endl;

  for(const auto &enemy : enemies)
  {
    futures.emplace_back(std::async(std::launch::async, &WaitingMissile::pushBack, queue, enemy));
  }

  futures.begin()->wait();

  while(queue->Size() > 0) {
    queue->attack = true;
    queue->popBack();
    std::cout << "queueuのサイズは: " << queue->Size() << std::endl;
  }
  Simurate(enemies);
}

void Missile::Update(Direction direction)
{
  // 敵と味方だと符号を反転させないと異形な
  if(direction == Direction::up)
  {
    y = y + 5.5;
  } else if (direction == Direction::down)
  {
    y = y + 1;
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