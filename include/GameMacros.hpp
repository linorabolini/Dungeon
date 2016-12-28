#ifndef GAMEMACROS_HPP
#define GAMEMACROS_HPP

#define LOG(msg) \
    std::cout << msg << std::endl;

#define WAIT(time) \
    sf::sleep(sf::milliseconds(time));

#endif /* GAMEMACROS_HPP */
