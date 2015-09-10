#pragma once

#include "Material.h"
#include "Eye.h"
#include "glm.hpp"

class Shape
{
public:
	
	glm::vec3 position;
	Material material;

	virtual bool intersect(const glm::vec3 rayDirection, const glm::vec3 rayOrigPos,float &t) = 0;
	virtual glm::vec3 getNormal(glm::vec3 intersectionPoint) = 0;
private:
	glm::vec3 normal;
};

