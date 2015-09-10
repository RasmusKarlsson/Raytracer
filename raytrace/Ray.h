#pragma once


#include <glm.hpp>
#include <ostream>
#include "Objects.h"

class Ray
{
protected:

	glm::vec3 orig,direction;
	
	int rayDepth;
	bool atWall,inside;

public:
	glm::vec3 color;
	
	Ray();
	//Ray(glm::vec3 o, glm::vec3 d, float near, float far);
	void Ray::createRay(glm::vec3 o, glm::vec3 d, float near, float far, int &depth, bool i);
	glm::vec3 Ray::trace(Objects o, int depth);


    /*
	Ray(glm::vec3 o, glm::vec3 d, float near = 1, float far = 100);

    glm::vec3 operator() (const float &t);
    
    glm::vec3 origin, dir, invdir;
    float tMin, tMax;
    bool sign[3];
    
    friend std::ostream& operator<<(std::ostream &os, const Ray &r);
	*/
};
