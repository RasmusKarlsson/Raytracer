#pragma once

#include <glm.hpp>;
#include "Eye.h"

Eye::Eye(glm::vec3 pos, float foven)
{
	position = pos;
	direction = glm::vec3(0,0,-1);
	up = glm::vec3(0,1,0);
	fov = foven;
}
