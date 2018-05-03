#pragma once
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\random.hpp>

class CellGrid
{
public:
	unsigned int sizex = 0;
	unsigned int sizey = 0;
private:
	GLuint *textures;
	unsigned int s;
	int *cellstate;

	float pixels[] = {
		0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f
	};


	CellGrid(unsigned int x = 4, unsigned int y = 4, unsigned int steps = 1)
	{
		sizex = x;
		sizey = y;
		s = steps;
		textures = new GLuint[s];
	}

	~CellGrid()
	{
	}
};

