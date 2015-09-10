#include "SolidCube.h"
#include <iostream>
#include <Windows.h>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include "glm.hpp"
#include <vector>
#define _USE_MATH_DEFINES // for C++
#include <cmath>

// Creates a solid cube

SolidCube::SolidCube(float height, float width, float depth, bool inside)
{
	h = height;
	w = width;
	d = depth;
	invertNormals = inside;

	cube_vertices.resize(36); //Number of vertices times 3 (x,y,z) times 2 (triangles/side)
    cube_normals.resize(36); //Number of normals times 3 (x,y,z) times 2 (triangles/side)
    cube_texcoords.resize(28); //Number of texcoordinates
	cube_indices.resize(36);
    std::vector<GLfloat>::iterator v = cube_vertices.begin();
    std::vector<GLfloat>::iterator n = cube_normals.begin();
    std::vector<GLfloat>::iterator t = cube_texcoords.begin();
	std::vector<GLushort>::iterator i = cube_indices.begin();

	// Vertices in 3D

		// Invert normals if we are inside the cube
			float inv = 1.0;
			if(invertNormals)
				inv = -1.0;
	
		*v++ = - 0.5f*w; // (0) Nedre främre vänstra hörnet
		*v++ = - 0.5f*h;
		*v++ = + 0.5f*d;
		// 1
		*v++ = + 0.5f*w; // (1) Nedre främre högra hörnet
		*v++ = - 0.5f*h;
		*v++ = + 0.5f*d;
		// 2
		*v++ = - 0.5f*w; // (2) Övre främre vänstra hörnet
		*v++ = + 0.5f*h;
		*v++ = + 0.5f*d;
		// 3
		*v++ = + 0.5f*w; // (3) Övre främre högra hörnet
		*v++ = + 0.5f*h;
		*v++ = + 0.5f*d;
		// 4
		*v++ = - 0.5f*w; // (4) Övre bakre vänstra hörnet
		*v++ = + 0.5f*h;
		*v++ = - 0.5f*d;
		// 5
		*v++ = + 0.5f*w; // (5) Övre bakre högra hörnet
		*v++ = + 0.5f*h;
		*v++ = - 0.5f*d;
		// 6
		*v++ = - 0.5f*w; // (6) Nedre bakre vänstra hörnet
		*v++ = - 0.5f*h;
		*v++ = - 0.5f*d;
		// 7
		*v++ = + 0.5f*w; // (7) Nedre bakre högra hörnet
		*v++ = - 0.5f*h;
		*v++ = - 0.5f*d;
	
	// Indices in 3D

		*i++ = 0; //Front
		*i++ = 1;
		*i++ = 2;
	
		*i++ = 2; //Front
		*i++ = 1;
		*i++ = 3;
	
		*i++ = 2; //Top
		*i++ = 3;
		*i++ = 4;
	
		*i++ = 4; //Top
		*i++ = 3;
		*i++ = 5;
	
		*i++ = 4; //Back
		*i++ = 5;
		*i++ = 6;
	
		*i++ = 6; //Back
		*i++ = 5;
		*i++ = 7;
	
		*i++ = 6; //Bottom
		*i++ = 7;
		*i++ = 0;
	
		*i++ = 0; //Bottom
		*i++ = 7;
		*i++ = 1;
	
		*i++ = 1; //Right
		*i++ = 7;
		*i++ = 3;
	
		*i++ = 3; //Right
		*i++ = 7;
		*i++ = 5;
	
		*i++ = 6; //Left
		*i++ = 0;
		*i++ = 4;
	
		*i++ = 4; //Left
		*i++ = 0;
		*i++ = 2;
	
	// Normals in 3D

		*n++ = 0.0f*inv; //Front
		*n++ = 0.0f*inv;
		*n++ = 1.0f*inv;

		*n++ = 0.0f*inv; //Front
		*n++ = 0.0f*inv;
		*n++ = 1.0f*inv;
	
		*n++ = 0.0f*inv; //Top
		*n++ = 1.0f*inv;
		*n++ = 0.0f*inv;
	
		*n++ = 0.0f*inv; //Top
		*n++ = 1.0f*inv;
		*n++ = 0.0f*inv;
	
		*n++ = 0.0f*inv; //Back
		*n++ = 0.0f*inv;
		*n++ = -1.0f*inv;
	
		*n++ = 0.0f*inv; //Back
		*n++ = 0.0f*inv;
		*n++ = -1.0f*inv;
	
		*n++ = 0.0f*inv; //Bottom
		*n++ = -1.0f*inv;
		*n++ = 0.0f*inv;
	
		*n++ = 0.0f*inv; //Bottom
		*n++ = -1.0f*inv;
		*n++ = 0.0f*inv;
	
		*n++ = 1.0f*inv; //Right
		*n++ = 0.0f*inv;
		*n++ = 0.0f*inv;
	
		*n++ = 1.0f*inv; //Right
		*n++ = 0.0f*inv;
		*n++ = 0.0f*inv;
	
		*n++ = -1.0f*inv; //Left
		*n++ = 0.0f*inv;
		*n++ = 0.0f*inv;
	
		*n++ = -1.0f*inv; //Left
		*n++ = 0.0f*inv;
		*n++ = 0.0f*inv;
	

	// Texture coordinates in 2D

		*t++ = 0.375000;
		*t++ = 0.000000;

		*t++ = 0.625000;
		*t++ = 0.000000;

		*t++ = 0.375000;
		*t++ = 0.250000;

		*t++ = 0.625000;
		*t++ = 0.250000;

		*t++ = 0.375000;
		*t++ = 0.500000;

		*t++ = 0.625000;
		*t++ = 0.500000;

		*t++ = 0.375000;
		*t++ = 0.750000;

		*t++ = 0.625000;
		*t++ = 0.750000;

		*t++ = 0.375000;
		*t++ = 1.000000;

		*t++ = 0.625000;
		*t++ = 1.000000;

		*t++ = 0.875000;
		*t++ = 0.000000;

		*t++ = 0.875000;
		*t++ = 0.250000;

		*t++ = 0.125000;
		*t++ = 0.000000;

		*t++ = 0.125000;
		*t++ = 0.250000;
}
	
void SolidCube::drawAt(GLfloat x, GLfloat y, GLfloat z) 
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x,y,z);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &cube_vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &cube_normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &cube_texcoords[0]);
	glColor4f( 1,0,0,1);
    glDrawElements(GL_TRIANGLES, cube_indices.size(), GL_UNSIGNED_SHORT, &cube_indices[0]);
    glPopMatrix();

	/*
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &cube_vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &cube_normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &cube_texcoords[0]);
	glColor4f( 1,0,0,1);
    glDrawElements(GL_TRIANGLES, cube_indices.size(), GL_UNSIGNED_SHORT, &cube_indices[0]);
    glPopMatrix();
	*/
}

SolidCube::~SolidCube(void)
{
}
