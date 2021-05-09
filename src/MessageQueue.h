#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>
#include <deque>

#include "Player.h"

struct Log {
  int x;
  int y;
  Player::Direction d;
};

template <class T>
class MessageQueue
{
public:
  void receive();
  void send(Log &&tl);
private:
  std::mutex _mutex;
  std::condition_variable _cond;
  std::deque<std::vector<Log>> _queue;
  bool is_finish{false};
};

#endif

// ミサイル発射ポジションをqueueにセットしてため込む
// 