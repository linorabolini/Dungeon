#pragma once
#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class Camera : public SceneNode
{
public:
    virtual void updateCurrent();
    void setTarget(SceneNode* target) { target_ = target; };
    void setZoom(float zoom);
    const sf::View getView() { return view_; }
    float targetZoom = 1.f;
private:
    float zoom_ = 1.f;
    sf::View view_;
    sf::Vector2f offset_ = sf::Vector2f(8*4, 0);
    SceneNode* target_ = NULL;
};

