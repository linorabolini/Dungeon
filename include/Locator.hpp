#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include <string>
#include <queue>
#include "CommandQueue.hpp"

class System
{
  public:
    void setResPath(std::string value) { resPath_ = value; }
    std::string getResPath() { return resPath_; }

    void setMapPath(std::string value) { mapPath_ = value; }
    std::string getMapPath() { return mapPath_; }

    void setSpriteSheetPath(std::string value) { spriteSheetPath_ = value; }
    std::string getSpriteSheetPath() { return spriteSheetPath_; }

  private:
    std::string resPath_;
    std::string mapPath_;
    std::string spriteSheetPath_;
};

class Locator
{
  public:
    static System *getSystem() { return system_; }
    static void provide(System* value) { system_ = value; }

    static CommandQueue *getCommandQueue() { return commandQueue_; }
    static void provide(CommandQueue* value) { commandQueue_ = value; }

  private:
    static System *system_;
    static CommandQueue *commandQueue_;
};
#endif /* LOCATOR_HPP */
