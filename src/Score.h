#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <memory>

class Score
{
  public:
    void CountScore();
    int getScore();
    Score(){}
    ~Score() { std::cout << "削除されたよ" << std::endl; }
  private:
    int _point{0};
};

#endif