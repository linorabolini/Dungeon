#include <Camera.hpp>

void Camera::updateCurrent()
{
    if(target_)
    {
        auto diff = target_->getWorldPosition() - view_.getCenter() + sf::Vector2f(8*4, 0);
        view_.move(diff * 0.01f);
    }
}

void Camera::setZoom(float zoom)
{
    view_.zoom(1.0f - zoom_ + zoom);
    zoom_ = zoom;
}