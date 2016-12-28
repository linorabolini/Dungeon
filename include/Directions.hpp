#ifndef DIRECTIONS_HPP
#define DIRECTIONS_HPP

#include <vector>

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

static std::vector<Direction>
    Directions
{
  Direction::UP,
  Direction::DOWN,
  Direction::LEFT,
  Direction::RIGHT
};

#endif /* DIRECTIONS_HPP */
