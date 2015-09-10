#include "Objects.h"


Objects::Objects(void)
{
	//Creating the objects

	//Sphere(4x4-matris, position, radius)
	//sphere1 = Sphere(glm::mat4(0.0),glm::vec3(0,0,10),0.3);

	
	//Plane(4x4-matris, position, width, height, depth) where one of the dimensions MUST be 0.0
	//plane1 = Plane(glm::mat4(0.0),glm::vec3(0,-0.3,10),0.5,0.0,0.5);
}

bool Objects::createNewSphere(const glm::mat4 ltw, glm::vec3 c, const float r)
{
	s = new Sphere(ltw, c, r);
	shapes.push_back(s);
	return true;
}

bool Objects::createNewPlane(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	//planes.push_back(Plane(p0,p1,p2,p3));
	s = new Plane(p0,p1,p2,p3);
	shapes.push_back(s);
	return true;
}

bool Objects::intersection(const glm::vec3 rayDirection, const glm::vec3 rayOrigPos, float &tMin, glm::vec3 &intersectionPoint, glm::vec3 &n, int &shapeID)
{
	float t = 999999.0;
	tMin = 99999.0;
	int reflObjID = shapeID;
	shapeID = -2;
	for(int i = 0; i < shapes.size(); i++)
	{
		bool hit = shapes[i]->intersect(rayDirection, rayOrigPos, t);
	
		if(t < tMin && t > 0.0001)	// Checks if the returned t is smaller than tMin
		{
			tMin = t;		// tMin becomes the t where the closest intersection ucour.
			shapeID = i;	// ID for the object with closest intersection.
		}
	}

	// Calculate the normal at the intersection point.

	if(tMin < 999999.0 && shapeID >= 0)
	{
		intersectionPoint = rayOrigPos + tMin*rayDirection;	// Specifies the intersection point.

		
		n = shapes[shapeID]->getNormal(intersectionPoint);

		return true;
	}
	else
	{
		return false;
	}
}
