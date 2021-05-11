#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <memory>
class Score
{
  public:
    Score(){}
    ~Score() { std::cout << "削除されたよ" << std::endl; }
    void CountScore();
    int getScore();
  private:
    int _point{0};
};

#endif