#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class Camera : public SceneNode
{
public:
    virtual void updateCurrent();
    void setTarget(SceneNode* target) { target_ = target; };
    void setZoom(float zoom);
    const sf::View getView() { return view_; }
private:
    float zoom_ = 1.f;
    sf::View view_;
    SceneNode* target_ = NULL;
};

#endif /* CAMERA_HPP */
