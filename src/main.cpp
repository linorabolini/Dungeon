#include <Game.hpp>
#include <iostream>
#include <unistd.h>
#include <Locator.hpp>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << " !!!! " << std::endl;
    }

    auto sys = new System();
    sys->setResPath("/Users/linorabolini/Documents/Projects/Cpp/SFML/Test/res/");

    Locator::provide(sys);

    Game game;
    game.run();

    delete sys;

    return 0;
}