#ifndef MOVECAMERACOMMAND_HPP
#define MOVECAMERACOMMAND_HPP

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

#endif /* MOVECAMERACOMMAND_HPP */
