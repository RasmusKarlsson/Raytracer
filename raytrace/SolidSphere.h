#pragma once
#include <iostream>
#include <Windows.h>
#include <gl\glew.h>
#include <gl\freeglut.h>
//#include <gl\glut.h>
#include "glm.hpp"
#include <vector>
#define _USE_MATH_DEFINES // for C++
#include <cmath>

class SolidSphere
{
	std::vector<GLfloat> sphere_vertices;
    std::vector<GLfloat> sphere_normals;
    std::vector<GLfloat> sphere_texcoords;
    std::vector<GLushort> sphere_indices;
public:
	//SolidSphere(void);
	SolidSphere(float radius, unsigned int rings, unsigned int sectors);
	void drawAt(GLfloat x, GLfloat y, GLfloat z);
	~SolidSphere(void);
};

