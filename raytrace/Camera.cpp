#include "Camera.h"

Camera::Camera() {
    position = glm::vec3(0, 0, 0);
    up = glm::vec3(0, 1, 0);
    lookAt = glm::vec3(0, 0, -1);
    fovX = 45*3.141592/180;
    fovY = fovX * 480.0 / 640.0;
}

Camera::~Camera(void)
{
}
