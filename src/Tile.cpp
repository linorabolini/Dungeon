#include <Tile.hpp>

std::vector<Tile *> Tile::getSurroundingTiles()
{
    std::vector<Tile *> tmp = {
        tileRight,
        tileLeft,
        tileUp,
        tileDown};
    std::vector<Tile *> result;

    for (auto &tile : tmp)
    {
        if (tile)
        {
            result.push_back(tile);
        }
    }

    return result;
}

void Tile::render(sf::RenderWindow* window)
{
    window->draw(sprite);

    if(unit) {
        unit->render(window);
    }
}