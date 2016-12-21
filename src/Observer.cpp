#include <Observer.hpp>

void Observer::on(std::string type, std::function<void(Event)> callback)
{
    callbacks_[type] = callback;
}
void Observer::off(std::string type)
{
    callbacks_.erase(type);
}
void Observer::notify(const Event event)
{
    if (callbacks_[event.type])
        callbacks_[event.type](event);
}
void Observer::trigger(const Event event)
{
    for (auto &target : targets_)
        target.second->notify(event);
}
void Observer::observe(Observer *target)
{
    target->addObserver(this);
}
void Observer::stopObserving(Observer *target)
{
    target->removeObserver(this);
}
void Observer::addObserver(Observer *target)
{
    targets_[target] = target;
}
void Observer::removeObserver(Observer *target)
{
    targets_.erase(target);
}
