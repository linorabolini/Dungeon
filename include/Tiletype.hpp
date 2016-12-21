#ifndef TILETYPE_HPP
#define TILETYPE_HPP

#include "Tileset.hpp"

class Tiletype : public XMLNode
{
  public:
    Tileset* tileset;
};

#endif /* TILETYPE_HPP */
