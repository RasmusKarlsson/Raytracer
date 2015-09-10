
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "SolidSphere.h"
#include <iostream>
#include <Windows.h>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include "glm.hpp"
#include <vector>



SolidSphere::SolidSphere(float radius, unsigned int rings, unsigned int sectors)
{
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;

    sphere_vertices.resize(rings * sectors * 3);
    sphere_normals.resize(rings * sectors * 3);
    sphere_texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = sphere_vertices.begin();
    std::vector<GLfloat>::iterator n = sphere_normals.begin();
    std::vector<GLfloat>::iterator t = sphere_texcoords.begin();
    for(r = 0; r < rings; r++){
		for(s = 0; s < sectors; s++) {
			float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
			float const y = sin( -M_PI_2 + M_PI * r * R );
			float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

			*t++ = s*S;
			*t++ = r*R;

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			*n++ = x;
			*n++ = y;
			*n++ = z;
		}
    }

    sphere_indices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = sphere_indices.begin();
    for(r = 0; r < rings; r++){
		for(s = 0; s < sectors; s++) {
			*i++ = r * sectors + s;
			*i++ = r * sectors + (s+1);
			*i++ = (r+1) * sectors + (s+1);
			*i++ = (r+1) * sectors + s;
		}
    }
}


void SolidSphere::drawAt(GLfloat x, GLfloat y, GLfloat z)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x,y,z);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &sphere_vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &sphere_normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &sphere_texcoords[0]);
	glColor4f( 1,0,0,1);
    glDrawElements(GL_QUADS, sphere_indices.size(), GL_UNSIGNED_SHORT, &sphere_indices[0]);
    glPopMatrix();
	//std::cout << "Sphere drawn!" << std::endl;
}
