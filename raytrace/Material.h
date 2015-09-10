#pragma once

#include "glm.hpp"

class Material
{
public:

	glm::vec3 color;
	bool isDiffuse,isRefractive;
	float specularReflectionIndex, refractiveIndex;

	Material(void);
	~Material(void);
};

