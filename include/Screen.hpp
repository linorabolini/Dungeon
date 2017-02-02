#pragma once
#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class Screen : public SceneNode
{
  public:
    virtual void load(){};
    virtual void unload(){};
};

