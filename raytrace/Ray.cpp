#include "ray.h"

Ray::Ray()
{
	orig = glm::vec3(0);
	direction = glm::vec3(0);
	//color = glm::vec3(1);
	rayDepth = 2;
	inside = false;
	atWall = false;
}
/*
Ray::Ray(glm::vec3 o, glm::vec3 d, float near, float far)
{
	orig = o;
	direction = d;
	//color = glm::vec3(1);
	rayDepth = 2;
	inside = false;
	atWall = false;
}
*/
void Ray::createRay(glm::vec3 o, glm::vec3 d, float near, float far, int &depth, bool i)
{
	orig = o;
	direction = d;
	color = glm::vec3(0);
	rayDepth = depth;
	inside = i;
	atWall = false;
}

glm::vec3 Ray::trace(Objects o, int depth)
{
	Objects obj = o;
	float t;
	int shapeID;
	glm::vec3 intersectionPoint = glm::vec3(0);
	glm::vec3 normal = glm::vec3(0);
	glm::vec3 reflDir = glm::vec3(0);
	glm::vec3 refrDir = glm::vec3(0);
	float indRef = 1.0f;
	int rayDepth = depth;
	float divideNumber1 = 1.0f;
	float divideNumber2 = 1.0f;

	glm::vec3 lightSource =glm::vec3(0,1.75,2);

	if(obj.intersection(direction, orig, t, intersectionPoint, normal, shapeID))
	{
		// Träff
		color = glm::vec3(0.0f);
		glm::vec3 reflcolor = glm::vec3(0.0f);
		glm::vec3 refrcolor = glm::vec3(0.0f);

			direction = glm::normalize(direction);
			
			intersectionPoint = orig + direction * t;
			normal = obj.shapes[shapeID]->getNormal(intersectionPoint);
			reflDir = glm::normalize(glm::reflect(direction, normal));
			glm::vec3 reflIntersection, refrIntersection;
		
		if(rayDepth > 0)
		{
		

			indRef = 1.0f/obj.shapes[shapeID]->material.refractiveIndex;
			if(inside) // If the ray is inside
			{
				indRef = 1.0f/indRef;
				refrDir = glm::normalize(glm::refract(direction, -normal, indRef));
				refrDir = glm::normalize(refrDir);
			}
			else // If the ray is outside
			{
				refrDir = glm::normalize(glm::refract(direction, normal, indRef));
				refrDir = glm::normalize(refrDir);
			}
			//refrDir = glm::normalize(glm::refract(direction, normal, indRef));
			Ray reflRay, refrRay;
			if(obj.shapes[shapeID]->material.isRefractive)
			{
				refrIntersection = intersectionPoint + 0.0001f * refrDir;
				refrRay.createRay(intersectionPoint, refrDir, 1.0, 100.0, --rayDepth, !inside);
				refrRay.trace(obj,rayDepth);
				refrcolor = refrRay.color;
			}
			else if(!obj.shapes[shapeID]->material.isDiffuse)
			{
				reflIntersection = intersectionPoint + 0.0001f * normal;
				reflRay.createRay(intersectionPoint, reflDir, 1.0, 100.0, --rayDepth, false);
				reflRay.trace(obj,rayDepth);
				reflcolor = reflRay.color;
			}
			else{
				reflcolor = glm::vec3(0);
				color = obj.shapes[shapeID]->material.color;

				rayDepth = 0;


				glm::vec3 lastIntersect = intersectionPoint;
				glm::vec3 lastNormal = normal;
				glm::vec3 lightDir = glm::normalize(lightSource - intersectionPoint);

				float lightDistance = glm::distance(lightSource, lastIntersect);
						
				float t2 = t;
				glm::vec3 normal2 = normal;
				int shapeID2 = shapeID;
				if(obj.intersection(lightDir, intersectionPoint - 0.0001f*direction, t2, lastIntersect, lastNormal, shapeID2)
					&& lightDistance > glm::distance(lastIntersect,intersectionPoint))
				{
					lightDistance = 6;
				}

				color *= 2.0f/glm::pow(lightDistance,1.5f);
				//refrcolor *=  (1.0f/divideNumber1)*1.0f/glm::pow(lightDistance,1.5f);
				reflcolor *=  1.0f/glm::pow(lightDistance,1.5f);


			}
			color = refrcolor + 0.9f*reflcolor + color;
			//color = 0.25f*refrcolor + 0.25f*reflcolor + color;
			//break;
		}
	}
	else
	{
		// Ingen träff
		color = glm::vec3(0,0,0);
	}
	return color;
}

