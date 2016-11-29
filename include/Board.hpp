#ifndef BOARD_HPP
#define BOARD_HPP

#include "Unit.hpp"
#include "Tile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
public:
    Board(int, int);
    ~Board();

    void update();
    void render(sf::RenderWindow* win_);
    int getColumns() { return cols_; };
    int getRows() { return rows_; };
    void addUnit(Unit* unit);
    std::vector<Unit*> getUnits() { return units_; };
    std::vector<Tile*> getTiles() { return tiles_; };
private:
    Board() {};
    int cols_ = 0;
    int rows_ = 0;
    std::vector<Unit*> units_;
    std::vector<Tile*> tiles_;
};

#endif /* BOARD_HPP */
