#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include "SceneNode.hpp"

class SpriteNode : public SceneNode
{
public:
    sf::Sprite sprite;
    virtual void renderCurrent(sf::RenderWindow* window) {
        window->draw(sprite);
    }
};


#endif /* SPRITENODE_HPP */
