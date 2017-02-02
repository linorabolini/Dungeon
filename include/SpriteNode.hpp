#pragma once
#include "SceneNode.hpp"

class SpriteNode : public SceneNode
{
public:
    sf::Sprite sprite;
    SpriteNode(){};
    SpriteNode(sf::Texture& texture) { sprite.setTexture(texture); };
    virtual void renderCurrent(sf::RenderWindow *window, const sf::Transform& parentTransform) const {
        window->draw(sprite, parentTransform);
    }
};

