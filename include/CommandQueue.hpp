#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include "Command.hpp"

class CommandQueue
{
  public:
    void push(Command cmd) { queue_.push(cmd); }
    Command pop()
    {
        auto cmd = queue_.front();
        queue_.pop();
        return cmd;
    }
    // void clear() { queue_.clear(); }
  private:
    std::queue<Command> queue_;
};

#endif /* COMMANDQUEUE_HPP */
