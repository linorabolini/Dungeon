#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <functional>
#include <vector>
#include <map>

class Event
{
  public:
    Event(int type) : type(type){};
    int type;
};

class Observer
{
  public:
    void on(int type, std::function<void(Event)> callback);
    void off(int type);
    void notify(const Event event);
    void trigger(const Event event);
    void observe(Observer *target);
    void stopObserving(Observer *target);
    void addObserver(Observer *target);
    void removeObserver(Observer *target);

  private:
    std::map<int, std::function<void(Event)>> callbacks_;
    std::map<Observer *, Observer *> targets_;
};

#endif /* OBSERVER_HPP */
