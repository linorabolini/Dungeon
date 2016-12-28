#include <Game.hpp>
#include <Locator.hpp>

int main(int argc, char *argv[])
{
    auto sys = new DirHelper();
    sys->setResPath("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/res/");
    sys->setMapPath(sys->getResPath() + "map/");
    sys->setSpriteSheetPath(sys->getResPath() + "spritesheet/");

    Locator::provide(sys);

    auto gm = new GameManager();
    Locator::provide(gm);

    Game game;
    game.run();

    delete sys;
    delete gm;

    return 0;
}