#ifndef LOCATOR_HPP
#define LOCATOR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include "GameManager.hpp"
#include "ResourceManager.hpp"

class GameManager;

class DirHelper
{
  public:
    void setResPath(std::string value) { resPath_ = value; }
    std::string getResPath() { return resPath_; }

    void setMapPath(std::string value) { mapPath_ = value; }
    std::string getMapPath() { return mapPath_; }

    void setFontPath(std::string value) { fontPath_ = value; }
    std::string getFontPath() { return fontPath_; }

    void setSpriteSheetPath(std::string value) { spriteSheetPath_ = value; }
    std::string getSpriteSheetPath() { return spriteSheetPath_; }

  private:
    std::string resPath_;
    std::string fontPath_;
    std::string mapPath_;
    std::string spriteSheetPath_;
};

class Locator
{
  public:
    static DirHelper *getDirHelper() { return dirHelper_; }
    static void provide(DirHelper* value) { dirHelper_ = value; }

    static GameManager *getGameManager() { return gameManager_; }
    static void provide(GameManager* value) { gameManager_ = value; }

    static ResourceManager *getResourceManager() { return resourceManager_; }
    static void provide(ResourceManager* value) { resourceManager_ = value; }

    static sf::Clock *getClock() { return &clock_; }
  private:
    static sf::Clock clock_;
    static DirHelper *dirHelper_;
    static GameManager *gameManager_;
    static ResourceManager *resourceManager_;
};
#endif /* LOCATOR_HPP */
