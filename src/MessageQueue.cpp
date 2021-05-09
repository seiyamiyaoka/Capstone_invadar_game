#include "MessageQueue.h"

template <typename T>
void MessageQueue<T>::receive()
{
  std::unique_lock<std::mutex> uLock(_mutex);
  _cond.wait(uLock, [this] { is_finish; });
  // T v = std::move(_queue.back());
  // _queue.pop_front();
  // return v;
  std::cout << "処理終了したら呼ばれる" << std::endl;
}

template <typename T>
void MessageQueue<T>::send(Log &&tl)
{
  std::lock_guard<std::mutex> uLock(_mutex);
    // review point perfomance speed up
    _queue.push_back(std::move(tl));
    _cond.notify_one();
}