#pragma once

#include "glm.hpp"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include <vector>
#include <iostream>
#include <iterator>

class Objects
{

public:
	/*
	std::vector<Sphere> spheres;
	std::vector<Plane> planes;
	*/
	std::vector<Shape*> shapes;
	Shape* s;

	int objectID;

	Objects(void);

	bool createNewSphere(const glm::mat4 ltw, glm::vec3 c, const float r);


	bool createNewPlane(glm::vec3 p0, glm::vec3 p1,  glm::vec3 p2, glm::vec3 p3);

	bool intersection(const glm::vec3 rayDirection, const glm::vec3 rayOrigPos, float &tMin, glm::vec3 &intersectionPoint, glm::vec3 &n, int &shapeID);
};

