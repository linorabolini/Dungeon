#pragma once
#include "Command.hpp"
#include <queue>

class CommandQueue
{
  public:
    void push(Command* cmd) {
      queue_.push(cmd);
    }
    Command* pop()
    {
        auto cmd = queue_.front();
        queue_.pop();
        return cmd;
    }
    bool isEmpty() { return queue_.empty(); };
  private:
    std::queue<Command*> queue_;
};
