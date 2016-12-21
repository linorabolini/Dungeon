#include <Camera.hpp>

void Camera::update()
{
    if(target_)
    {
        view_.setCenter(target_->getPosition());
    }
}

void Camera::setZoom(float zoom)
{
    view_.zoom(1.0f - zoom_ + zoom);
    zoom_ = zoom;
}