#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Camera : public GameObject
{
public:
    virtual void update();
    void setTarget(sf::Transformable* target) { target_ = target; };
    void setZoom(float zoom);
    const sf::View getView() { return view_; }
private:
    float zoom_ = 1.f;
    sf::View view_;
    sf::Transformable* target_ = NULL;
};

#endif /* CAMERA_HPP */
