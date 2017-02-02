#pragma once
#include <functional>
#include <vector>
#include <map>
#include <string>

namespace dungeon 
{

struct Event
{
    Event(std::string type_) : type(type_) {};
    Event();
    std::string type;
};

class Observer
{
  public:
    void on(std::string type, std::function<void(Event)> callback);
    void off(std::string type);
    void notify(const Event event);
    void trigger(const Event event);
    void observe(Observer *target);
    void stopObserving(Observer *target);
    void addObserver(Observer *target);
    void removeObserver(Observer *target);

  private:
    std::map<std::string, std::function<void(Event)>> callbacks_;
    std::map<Observer *, Observer *> targets_;
};
}
