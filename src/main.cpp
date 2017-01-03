#include <Game.hpp>
#include <Locator.hpp>

int main(int argc, char *argv[])
{
    auto sys = new DirHelper();
    sys->setResPath("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/res/");
    sys->setMapPath(sys->getResPath() + "map/");
    sys->setFontPath(sys->getResPath() + "font/");
    sys->setSpriteSheetPath(sys->getResPath() + "spritesheet/");

    Locator::provide(sys);

    auto gm = new GameManager();
    Locator::provide(gm);

    auto resourceManager = new ResourceManager();
    Locator::provide(resourceManager);

    Game game;
    game.run();

    delete sys;
    delete gm;

    return 0;
}