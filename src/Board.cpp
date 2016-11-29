#include <Board.hpp>

Board::Board(int rows, int cols)
{
    rows_ = rows;
    cols_ = cols;
    tiles_.resize(rows_ * cols_);
}

Board::~Board()
{
    
}

void Board::addUnit(Unit* unit)
{
    units_.push_back(unit);
}

void Board::update()
{
}

void Board::render(sf::RenderWindow* win_)
{
    int separation = 50;
    sf::Vector2f v(separation, separation);
    sf::RectangleShape shape(v);
    sf::Color c;
   
    int x_pos;
    int y_pos;
    int row_color_factor;

    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    int size = tiles_.size();
    for (int i = 0; i < size; i++)
    {
        x_pos = i % rows_ * separation;
        y_pos = i / rows_ * separation;

        row_color_factor = 50 + y_pos * 180 / (cols_ * separation);
        c = sf::Color(row_color_factor,row_color_factor,row_color_factor);
        shape.setFillColor(c);
        shape.setPosition(x_pos, y_pos);
        win_->draw(shape);
    }
}