#ifndef SPHERE_H
#define SPHERE_H

#include <glm.hpp>
#include "Shape.h"
#include "Material.h"

class Sphere: public Shape
{
public:
	
    float radius, radiusSq;

	Sphere();
    Sphere(const glm::mat4 ltw, glm::vec3 c, const float r);
	bool intersect(const glm::vec3 rayDirection, const glm::vec3 rayOrigPos,float &t);
	glm::vec3 getNormal(glm::vec3 intersect);

};

#endif // SPHERE_H