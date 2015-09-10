#pragma once

#include <glm.hpp>
#include "Shape.h"
#include "Material.h"

class Plane: public Shape
{
public:

	glm::vec3 pos0,pos1,pos2,pos3,normal;
	
	Plane(void);
	Plane(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	bool intersect(const glm::vec3 rayDirection, const glm::vec3 rayOrigPos,float &t);
	glm::vec3 getNormal(glm::vec3 intersect);
};

