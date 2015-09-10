#include <gl\glew.h>
#include <gl\freeglut.h>
#include "glm.hpp"
#include "ImportObject.h"
#include <string>
#include <vector>
#include <map>

ImportObject::ImportObject(const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals)
{

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file !\n");
	}
	while( true ){
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
    
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		// For each vertex of each triangle

	}
	for( unsigned int i=0; i<vertexIndices.size(); i++ )
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		out_vertices.push_back(vertex);
	}
	for( unsigned int i=0; i<uvIndices.size(); i++ )
	{
		unsigned int uvIndex =	   uvIndices[i];
		glm::vec2 uvs = temp_uvs[ uvIndex-1 ];
		out_uvs.push_back(uvs);
	}

	for( unsigned int i=0; i<normalIndices.size(); i++ )
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		out_normals.push_back(normal);
	}
	/*
	int i, vertexCount, triangleCount;
	int *newCoords, *newNormalsIndex, *newTextureIndex;



	newCoords = new int[vertexIndices.size() * 3];
	if (theMesh->normalsIndex != NULL)
		newNormalsIndex = new int[triangleCount * 3];
	if (theMesh->textureIndex != NULL)
		newTextureIndex = new int[triangleCount * 3];

	// 1.2 Loop through old list and write the new one
	// Almost same loop but now it has space to write the result
	vertexCount = 0;
	int newIndex = 0; // Index in newCoords
	int first = 0;
	for (i = 0; i < theMesh->coordCount; i++)
	{
		if (theMesh->coordIndex[i] == -1)
		{
			first = i + 1;
			vertexCount = 0;
		}
		else
		{
			vertexCount = vertexCount + 1;

			if (vertexCount > 2)
			{
				newCoords[newIndex++] = theMesh->coordIndex[first];
				newCoords[newIndex++] = theMesh->coordIndex[i-1];
				newCoords[newIndex++] = theMesh->coordIndex[i];

				if (theMesh->normalsIndex != NULL)
				{
					newNormalsIndex[newIndex-3] = theMesh->normalsIndex[first];
					newNormalsIndex[newIndex-2] = theMesh->normalsIndex[i-1];
					newNormalsIndex[newIndex-1] = theMesh->normalsIndex[i];
				}

				// Dito for textures
				if (theMesh->textureIndex != NULL)
				{
					newTextureIndex[newIndex-3] = theMesh->textureIndex[first];
					newTextureIndex[newIndex-2] = theMesh->textureIndex[i-1];
					newTextureIndex[newIndex-1] = theMesh->textureIndex[i];
				}

			}
		}
	}

	free(theMesh->coordIndex);
	theMesh->coordIndex = newCoords;
	theMesh->coordCount = triangleCount * 3;
	if (theMesh->normalsIndex != NULL)
	{
		free(theMesh->normalsIndex);
		theMesh->normalsIndex = newNormalsIndex;

	}
	if (theMesh->textureIndex != NULL)
	{
		free(theMesh->textureIndex);
		theMesh->textureIndex = newTextureIndex;

	}
} // DecomposeToTriangles
*/
}

ImportObject::~ImportObject(void)
{
}