#pragma once
#include <SFML/Graphics.hpp>
#include "Command.hpp"
#include "System.hpp"
#include "Camera.hpp"

class Camera;

class SetCameraZoom : public Command
{
public:
    SetCameraZoom(Camera* camera, float zoom) : camera(camera_), zoom_(zoom){};
    virtual void execute(){
        camera_->setZoom(zoom_);
    };
private:
    float zoom_; 
};

