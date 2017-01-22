#include <Camera.hpp>

void Camera::updateCurrent()
{
    if(target_)
    {
        auto diff = target_->getWorldPosition() - view_.getCenter() + offset_;
        view_.move(diff * 0.01f);
    }
    if(targetZoom != zoom_)
    {
        setZoom(targetZoom);
    }
}

void Camera::setZoom(float zoom)
{
    view_.zoom(1.0f - zoom_ + zoom);
    targetZoom = zoom_ = zoom;
}