#include <Game.hpp>
#include <iostream>
#include <unistd.h>
#include <Locator.hpp>

int main(int argc, char *argv[])
{
    auto sys = new System();
    sys->setResPath("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/res/");

    Locator::provide(sys);

    Game game;
    game.run();

    delete sys;

    return 0;
}