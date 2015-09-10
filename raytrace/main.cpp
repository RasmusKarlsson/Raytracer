#include <iostream>
#include <Windows.h>
#include <gl\glew.h>
#include <gl\freeglut.h>
//#include <gl\glut.h>
#include "Eye.h"
#include "Ray.h"
#include "Objects.h"
#include "Sphere.h"
#include "glm.hpp"
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h> //calc rendertime
//#include <omp.h> //Use multicore processors
#include <random>

#define NEAR 1.0
#define FAR 1500.0
#define RIGHT 0.5
#define LEFT -0.5
#define TOP 0.5
#define BOTTOM -0.5

#define W 512
#define H 512

#define RED glm::vec3(0.9,0.1,0.1);
#define GREEN glm::vec3(0.1,0.9,0.1);
#define BLUE glm::vec3(0.1,0.1,0.9);
#define YELLOW glm::vec3(0.9,0.9,0.1);
#define CYAN glm::vec3(0.1,0.9,0.9);
#define MAGENTA glm::vec3(1,0.1,0.9);
#define WHITE glm::vec3(0.9,0.9,0.9);
#define BLACK glm::vec3(0.1,0.1,0.1);



#define PI 3.14159265359
void drawScene(void);

 //pixels;	
GLuint imageTexture = 0;
int renderWidth = 512;
int renderHeight = 512;

unsigned char *pixels = new unsigned char[renderWidth*renderHeight*3];


glm::vec3 shootRay();

float FieldOfView = PI/6; //Degrees

Eye camera = Eye(glm::vec3(0,0,7.6), FieldOfView);

float pixelPlane = 4.0;

void init(void)
{
	float seconds = glutGet(GLUT_ELAPSED_TIME);

	 Objects obj;

	 float raysPerPixel = 9.0f;
	 int rays = int(raysPerPixel);

	float X =2;
	float Y =2;
	float Z =0;
	float cornellDepth = 5.0f;
	
	 //CornellBox Walls
	 obj.createNewPlane(glm::vec3(-X,-Y,Z),glm::vec3(X,-Y,Z),glm::vec3(X,Y,Z),glm::vec3(-X,Y,Z));
	 obj.createNewPlane(glm::vec3(-X,-Y,Z+cornellDepth),glm::vec3(-X,-Y,Z),glm::vec3(-X,Y,Z),glm::vec3(-X,Y,Z+cornellDepth));
	 obj.createNewPlane(glm::vec3(-X,-Y,Z+cornellDepth),glm::vec3(X,-Y,Z+cornellDepth),glm::vec3(X,-Y,Z),glm::vec3(-X,-Y,Z));
	 obj.createNewPlane(glm::vec3(X,-Y,Z),glm::vec3(X,-Y,Z+cornellDepth),glm::vec3(X,Y,Z+cornellDepth),glm::vec3(X,Y,Z));
	 obj.createNewPlane(glm::vec3(-X,Y,Z),glm::vec3(X,Y,Z),glm::vec3(X,Y,Z+cornellDepth),glm::vec3(-X,Y,Z+cornellDepth));
	 //And their Colors
	 obj.shapes[0]->material.color = GREEN;
	 obj.shapes[1]->material.color = MAGENTA;
	 obj.shapes[2]->material.color = YELLOW;
	 obj.shapes[3]->material.color = BLUE;
	 obj.shapes[4]->material.color = RED;
	 
	 //Box made up of 6 planes
	 float boxY = 0.525;
	 obj.createNewPlane(glm::vec3(-1.587,-2.0,1.819),glm::vec3(-0.361,-2.000,2.120),glm::vec3(-0.361,0.525,2.120),glm::vec3(-1.587,0.525,1.819));
	 obj.createNewPlane(glm::vec3(-0.361,-2.0,2.120),glm::vec3(-0.060,-2.000,0.894),glm::vec3(-0.060,0.525,0.894),glm::vec3(-0.361,0.525,2.120));
	 obj.createNewPlane(glm::vec3(-0.060,-2.0,0.894),glm::vec3(-1.286,-2.000,0.593),glm::vec3(-1.286,0.525,0.593),glm::vec3(-0.060,0.525,0.894));
	 obj.createNewPlane(glm::vec3(-1.286,-2.0,0.593),glm::vec3(-1.587,-2.000,1.819),glm::vec3(-1.587,0.525,1.819),glm::vec3(-1.286,0.525,0.593));
	 //top
	 obj.createNewPlane(glm::vec3(-1.587,0.525,1.819),glm::vec3(-0.361,0.525,2.120),glm::vec3(-0.060,0.525,0.894),glm::vec3(-1.286,0.525,0.593));
	 float SphereRadius = 0.80;
	 obj.createNewSphere(glm::mat4(0.0),glm::vec3(0.7,-2.0+SphereRadius,Z+3.0),SphereRadius);

	 obj.shapes[5]->material.color = BLUE;
	 obj.shapes[6]->material.color = RED;
	 obj.shapes[7]->material.color = YELLOW;
	 obj.shapes[8]->material.color = MAGENTA;
	 obj.shapes[9]->material.color = CYAN;

	 obj.shapes[10]->material.isDiffuse = false;
	 obj.shapes[10]->material.isRefractive = true;
	obj.shapes[10]->material.refractiveIndex = 1.5f; //Originally 1.33f
	 obj.shapes[10]->material.color = YELLOW;

	  obj.createNewPlane(glm::vec3(-X*20,-Y*20,Z+7.7),glm::vec3(-X*20,Y*20,Z+7.7),glm::vec3(X*20,Y*20,Z+7.7),glm::vec3(X*20,-Y*20,Z+7.7));

	  obj.shapes[11]->material.color = CYAN;

	 obj.shapes[5]->material.isDiffuse = false;
	 obj.shapes[6]->material.isDiffuse = false;
	 obj.shapes[7]->material.isDiffuse = false;
	 obj.shapes[8]->material.isDiffuse = false;
	 obj.shapes[9]->material.isDiffuse = false;



	 obj.createNewSphere(glm::mat4(0.0),glm::vec3(-1.0,-2.0+0.6,Z+3.0),0.6);
	 obj.shapes[12]->material.isDiffuse = false;


	//======== Main RayTracing Loop ========
		glm::vec3 renderColor,pixelColor = BLACK;
		glm::vec3 lightSource =glm::vec3(0,1.75,2);

		float yFov = 0.5*renderHeight / (camera.position.z*sin(FieldOfView/2.0));
		float xFov = 0.5*renderWidth / (camera.position.z*sin(FieldOfView*(renderWidth/renderHeight)/2.0));

		float maxT = -10.0;
			float minT = 9999999.9;


		float SSx [9];
			
		SSx[0] = -1.0/3.0;
		SSx[1] = 0.0;
		SSx[2] = 1.0/3.0;
		SSx[3] = -1.0/3.0;
		SSx[4] = 0.0;
		SSx[5] = 1.0/3.0;
		SSx[6] = -1.0/3.0;
		SSx[7] = 0.0;
		SSx[8] = 1.0/3.0;


		float SSy [9];

		SSy[0] = 1.0/3.0;
		SSy[1] = 1.0/3.0;
		SSy[2] = 1.0/3.0;
		SSy[3] = 0.0;
		SSy[4] = 0.0;
		SSy[5] = 0.0;
		SSy[6] = -1.0/3.0;
		SSy[7] = -1.0/3.0;
		SSy[8] = -1.0/3.0;
		
		srand((unsigned)time(NULL));
		float shadow = 1.0;

		for (int x=0; x<renderWidth; x++) 
		{	
			for (int y=0; y<renderHeight; y++) 
			{
				shadow = 1.0;
				renderColor = glm::vec3(0);


				
				for (int i=0; i<rays; i++) 
				{
					SSx[i] += 0.01*((((float)rand() / (float)RAND_MAX)/3.75) -1.0/7.5);
					SSy[i] += 0.01*((((float)rand() / (float)RAND_MAX)/3.75) -1.0/7.5);
				}
				
				for (int c=0; c<rays; c++) 
				{
					pixelColor = glm::vec3(0);
					glm::vec3 rayDirection = glm::vec3((x+SSx[c]-renderWidth/2.0)/yFov,(y+SSy[c]-renderHeight/2.0)/yFov,pixelPlane) - camera.position;

					rayDirection = glm::normalize(rayDirection);


					bool insideObject = false;
					bool hitWall = false;
					int rayDepth = 1;
					float t = 999999.0;
					float tMin = 999999.0;
					int objectID = -1;
					float lastRefIndex = 1.3333;
					int maxDepth = 12;


					Ray ray = Ray();
					ray.createRay(camera.position,rayDirection,1.0f,100.0f,maxDepth, false);
					ray.trace(obj,maxDepth);
					renderColor += ray.color;
					
				}
				

				renderColor.r = glm::min(renderColor.r/raysPerPixel,1.0f);
				renderColor.g = glm::min(renderColor.g/raysPerPixel,1.0f);
				renderColor.b = glm::min(renderColor.b/raysPerPixel,1.0f);

				pixels[3*(y*renderWidth+x)] = 255*renderColor.r;
				pixels[3*(y*renderWidth+x)+1] = 255*renderColor.g;
				pixels[3*(y*renderWidth+x)+2] = 255*renderColor.b;

				
			}
			std::cout << "progress: " << x << " / " << renderWidth << " done" << std::endl;
		}


		float ms = (glutGet(GLUT_ELAPSED_TIME) - seconds);

		std::cout << "RenderTime: " << ms << " milliseconds" << std::endl;
		//  (0,480)----------------- (640,480)
		//         |               |
		//         |   The Screen  |
		//         |               |
		//         |               |
		//    (0,0)----------------- (640,0)


	printf("OpenGL Version:%s\n",glGetString(GL_VERSION));
	printf("GLSL Version  :%s\n\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

		glGenTextures( 1, &imageTexture );
	glBindTexture( GL_TEXTURE_2D, imageTexture);

		
}


void drawScene(void)
{
	


}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glTexParameterf( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, renderWidth, renderHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels );

		glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
		glShadeModel(GL_SMOOTH);     

		glBegin (GL_QUADS);
			glTexCoord2d(0.0,0.0);
			glVertex2d(-1.0,-1.0);

			glTexCoord2d(0.0,1.0);
			glVertex2d(-1.0,+1.0);

			glTexCoord2d(1.0,1.0);
			glVertex2d(+1.0,+1.0);

			glTexCoord2d(1.0,0.0);
			glVertex2d(+1.0,-1.0);
		glEnd();

		//glColor4f(1, 1, 1, 1);
	
   
	/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);
	gluQuadricTexture(sphere1,1);
	*/
	
	//glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 2);
	//gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//gluSphere(sphere1,2.0, 20, 20);
	//size = size -0.0001;


	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	//glDrawElements(GL_TRIANGLES, vertices.size() * sizeof(glm::vec3), GL_UNSIGNED_SHORT, &vertices);
	
    //sphere->drawAt(0.0f,-4.0f,0.0f);
	//cube->drawAt(4.0f,4.0f,-10.0f);
/*
	glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
   // glVertex3f(cube->);
    //glVertex3f((face.getCenter().x+face.getNormal().x), (face.getCenter().y+face.getNormal().y), (face.getCenter().z+face.getNormal().z));
    glEnd();

*/
	//glDisable(GL_LIGHTING);
    glutSwapBuffers();
}

void idle()
{
	//glutPostRedisplay();
	//std::cout << "Klar!";
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w/(GLfloat)h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(W, H);
	glutCreateWindow ("Raytracer");
	//glewInit();

	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); 
	glutDisplayFunc(display);

	//glutSwapBuffers();

	init();

	glutMainLoop();
}