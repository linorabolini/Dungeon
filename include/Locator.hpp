#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include <string>
#include "camera.hpp"

class System
{
  public:
    void setResPath(std::string value) { resPath_ = value; }
    std::string getResPath() { return resPath_; }

  private:
    std::string resPath_;
};

class Locator
{
  public:
    static System *getSystem() { return system_; }
    static void provide(System* value)
    {
        system_ = value;
    }

  private:
    static System *system_;
};
#endif /* LOCATOR_HPP */
