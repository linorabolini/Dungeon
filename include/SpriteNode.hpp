#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include "SceneNode.hpp"

class SpriteNode : public SceneNode
{
public:
    sf::Sprite sprite;
    virtual void renderCurrent(sf::RenderWindow *window, const sf::Transform& parentTransform) const {
        window->draw(sprite, parentTransform);
    }
};


#endif /* SPRITENODE_HPP */
