#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/constants.hpp>
#include <algorithm>

#include "Ray.h"


class Camera
{
public:
    Camera();
    //Camera(glm::vec3 p, glm::vec3 u, glm::vec3 la, float fx, int w, int h);
	~Camera();
    
    glm::vec3 position, up, lookAt;
    
    float fovX, fovY;

private:
    
};

#endif // CAMERA_H