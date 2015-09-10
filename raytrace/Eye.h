#ifndef EYE_H
#define EYE_H

#include "glm.hpp"

class Eye
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	float fov;

	Eye(glm::vec3 pos, float fov);

};

#endif // EYE_H
