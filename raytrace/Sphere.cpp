#include <iostream>
#include "Sphere.h"

Sphere::Sphere()
{
	position = glm::vec3(0);
	radius = 0.0;
}

Sphere::Sphere(const glm::mat4 ltw, glm::vec3 c, const float r)
{
	position = c;
    radius = r;
    radiusSq = r * r;
}

bool Sphere::intersect(const glm::vec3 rayDirection, const glm::vec3 rayOrigPos,float &t)
{
    //Compute A, B and C coefficients
    /*
	float a = glm::dot(ray.dir, ray.dir);
    float b = 2 * glm::dot(ray.dir, ray.origin);
    float c = glm::dot(ray.origin, ray.origin) - radiusSq;
	*/
	float a = glm::dot(rayDirection,rayDirection);
	float b = 2.0*glm::dot(rayDirection,rayOrigPos - position);
	float c = glm::dot(rayOrigPos - position,rayOrigPos - position) - radiusSq;
    //Find discriminant
    float disc = b * b - 4 * a * c;
    
    // if discriminant is negative there are no real roots, so return 
    // false as ray misses sphere
    if (disc <= 0)
        return false;

	float t0 =  (-b + sqrt(b * b - 4 * a * c)) / (2 *a);
	float t1 =  (-b - sqrt(b * b - 4 * a * c)) / (2 *a);
	
    // make sure t0 is smaller than t1
    if (t0 > t1)
    {
        // if t0 is bigger than t1 swap them around
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

	/*
    // if t1 is less than zero, the object is in the ray's negative direction
    // and consequently the ray misses the sphere
    if (t1 < 0)
        return true;
	*/
    // if t0 is less than zero, the intersection point is at t1
    if (t0 < 0)
    {
        t = t1;
        return true;
    }
    // else the intersection point is at t0
    else
    {
        t = t0;
        return true;
    }
	
}

glm::vec3 Sphere::getNormal(glm::vec3 intersectionPoint){
	return glm::normalize((intersectionPoint - position));
}