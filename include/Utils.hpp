#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <Locator.hpp>

class Utils
{
public:
    static sf::Rect<int> getRectForTilemap(int x, int y,int w,int h,int spacing=2,int margin=1) {
        sf::Rect<int> rect;
        rect.top = y * h + y * spacing + margin;
        rect.height = h;
        rect.left = x * w + x * spacing + margin;
        rect.width = w;
        return rect;
    }
};

#endif /* UTILS_HPP */
