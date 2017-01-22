#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class Screen : public SceneNode
{
  public:
    virtual void load(){};
    virtual void unload(){};
};

#endif /* SCREEN_HPP */
