#pragma once
#include <iostream>
#include <Windows.h>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include "glm.hpp"
#include <vector>
#define _USE_MATH_DEFINES // for C++
#include <cmath>

class SolidCube
{
protected:

	GLfloat h,w,d;
	bool invertNormals;
	
	std::vector<GLfloat> cube_vertices;
    std::vector<GLfloat> cube_normals;
    std::vector<GLfloat> cube_texcoords;
    std::vector<GLushort> cube_indices;
public:
	SolidCube(float height, float width, float depth, bool inside);
	void drawAt(GLfloat x, GLfloat y, GLfloat z);
	~SolidCube(void);
};

