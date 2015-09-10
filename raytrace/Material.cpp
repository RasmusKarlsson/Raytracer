#include "Material.h"


Material::Material(void)
{
	color = glm::vec3(0,1,0);
	specularReflectionIndex = 1.0;
	refractiveIndex = 1.0;
	isDiffuse = true;
	isRefractive = false;
}

Material::~Material(void)
{
}
